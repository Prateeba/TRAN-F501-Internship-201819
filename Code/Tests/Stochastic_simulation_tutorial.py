from matplotlib import colors
from matplotlib import pyplot
from numpy import linalg
from scipy import integrate
from scipy import optimize
from scipy import stats
import matplotlib
import numpy
import os

# Directory path in which to save the different results
OUT_DIR = os.path.join(os.path.dirname(__file__), '.', 'simulation')

class SsaSimulation(object):
    """ Represents an SSA simulation of mRNA and protein synthesis and degradation
    Attributes:
        k_m :  mRNA synthesis rate constant 
        k_n : protein synthesis rate constant 
        gamma_m : mRNA degradation rate constant 
        gamma_n : protein degradation rate constant 
        m_0 : initial mRNA number (molecules)
        n_0 : initial protein number (molecules)
    """

    def __init__(self, k_m=5, k_n=20, gamma_m=numpy.log(2) * 60 / 3, gamma_n=numpy.log(2) / 10, m_0=1, n_0=98):
        """
        Args:
            k_m : mRNA synthesis rate constant 
            k_n : protein synthesis rate constant 
            gamma_m : mRNA degradation rate constant 
            gamma_n : protein degradation rate constant 
            m_0 : initial mRNA number (molecules)
            n_0 : initial protein number (molecules)
        """
        self.k_m = k_m
        self.k_n = k_n
        self.gamma_m = gamma_m
        self.gamma_n = gamma_n
        self.m_0 = m_0
        self.n_0 = n_0

    # reaction rates
    def r_m_syn(self, m, n):
        """ Calculate the mRNA synthesis rate
        Args:
            m (:obj:`float`): mRNA number (molecules)
            n (:obj:`float`): protein number (molecules)
        Returns:
            :obj:`float`: mRNA synthesis rate (molecules h\ :sup:`-1`)
        """
        return self.k_m

    def r_n_syn(self, m, n):
        """ Calculate the protein synthesis rate
        Args:
            m (:obj:`float`): mRNA number (molecules)
            n (:obj:`float`): protein number (molecules)
        Returns:
            :obj:`float`: protein synthesis rate (molecules h\ :sup:`-1`)
        """
        return m * self.k_n

    def r_m_deg(self, m, n):
        """ Calculate the mRNA degradation rate
        Args:
            m (:obj:`float`): mRNA number (molecules)
            n (:obj:`float`): protein number (molecules)
        Returns:
            :obj:`float`: mRNA degradation rate (molecules h\ :sup:`-1`)
        """
        return m * self.gamma_m

    def r_n_deg(self, m, n):
        """ Calculate the protein degradation rate
        Args:
            m (:obj:`float`): mRNA number (molecules)
            n (:obj:`float`): protein number (molecules)
        Returns:
            :obj:`float`: protein degradation rate (molecules h\ :sup:`-1`)
        """
        return n * self.gamma_n

    def sample_initial_conditions(self):
        """ Sample initial mRNA and protein copy numbers
        Returns:
            :obj:`tuple`:
                * :obj:`int`: initial mRNA copy number
                * :obj:`int`: initial protein copy number
        """
        m = numpy.random.poisson(self.k_m / self.gamma_m)
        n = numpy.round(numpy.random.gamma(self.k_m / self.gamma_n, self.k_n / self.gamma_m))
        return (m, n)

    def simulate(self, t_0=0., t_end=100., t_step=1.):
        """ Run the simulation
        Args:
            t_0 (:obj:`float`, optional): initial time (h)
            t_end (:obj:`float`, optional): end time (h)
            t_step (:obj:`float`, optional): frequency at which to record predicted mRNA and proteins
        Return:
            :obj:`tuple`:
                * :obj:`numpy.array`: simulation time (h)
                * :obj:`numpy.array`: predicted mRNA (molecules)
                * :obj:`numpy.array`: predicted proteins (molecules)
        """
        assert ((t_end - t_0) / t_step % 1 == 0)
        t_hist = numpy.linspace(t_0, t_end, int((t_end - t_0) / t_step) + 1)

        # data structure to store predicted copy numbers
        m_hist = numpy.full(t_hist.shape, self.m_0)
        n_hist = numpy.full(t_hist.shape, self.n_0)

        # initial conditions
        t = t_hist[0]
        m = self.m_0
        n = self.n_0

        # iterate over time
        while t < t_hist[-1]:
            # calculate reaction properties/rates
            propensities = numpy.array([
                self.r_m_syn(m, n),
                self.r_m_deg(m, n),
                self.r_n_syn(m, n),
                self.r_n_deg(m, n),
            ])
            total_propensity = numpy.sum(propensities)

            # select the length of the time step from an exponential distributuon
            dt = numpy.random.exponential(1. / total_propensity)

            # select the next reaction to fire
            i_reaction = numpy.random.choice(4, p=propensities / total_propensity)

            # update the time
            t += dt

            # update the copy numbers based on the selected reaction
            if i_reaction == 0:
                m += 1
            elif i_reaction == 1:
                m -= 1
            elif i_reaction == 2:
                n += 1
            else:
                n -= 1

            # store copy number history
            m_hist[t < t_hist] = m
            n_hist[t < t_hist] = n

        return (t_hist, m_hist, n_hist)

    def simulate_ensemble(self, n_trajectories=50, t_0=0., t_end=100., t_step=1.):
        """ Run multiple simulations
        Args:
            n_trajectories (:obj:`int`, optional): number of simulation to run
            t_0 (:obj:`float`, optional): initial time (h)
            t_end (:obj:`float`, optional): end time (h)
            t_step (:obj:`float`, optional): frequency at which to record predicted mRNA and proteins
        Return:
            :obj:`tuple`:
                * :obj:`numpy.array`: simulation time (h)
                * :obj:`numpy.array`: predicted mRNA (molecules)
                * :obj:`numpy.array`: predicted proteins (molecules)
        """
        assert ((t_end - t_0) / t_step % 1 == 0)
        t = numpy.linspace(t_0, t_end, int((t_end - t_0) / t_step) + 1)
        m = numpy.zeros((t.size, n_trajectories))
        n = numpy.zeros((t.size, n_trajectories))
        for i_trajectory in range(n_trajectories):
            self.m_0, self.n_0 = self.sample_initial_conditions()
            _, m[:, i_trajectory], n[:, i_trajectory] = self.simulate(t_0=t_0, t_end=t_end, t_step=t_step)

        return (t, m, n)

    def plot_trajectories(self, t, m, n):
        """ Plot multiple trajectories
        Args:
            t (:obj:`numpy.array`): simulation time (h)
            m (:obj:`numpy.array`): predicted mRNA (molecules)
            n (:obj:`numpy.array`): predicted proteins (molecules)
        Return:
            :obj:`matplotlib.figure.Figure`: figure
        """
        fig, axes = pyplot.subplots(nrows=2, ncols=1)

        n_trajectories = m.shape[1]

        for i_trajectory in range(n_trajectories):
            if n_trajectories == 1:
                gray = 0.
            else:
                gray = 0.5 - 0.5 * i_trajectory / (n_trajectories - 1)
            axes[0].plot(t, m[:, i_trajectory], color=(gray, gray, gray))
            axes[1].plot(t, n[:, i_trajectory], color=(gray, gray, gray))

        axes[0].set_xlim((t[0], t[-1]))
        axes[1].set_xlim((t[0], t[-1]))

        axes[0].set_ylim([0, numpy.max(m) + 1])
        axes[1].set_ylim([numpy.min(n) - 5, numpy.max(n) + 5])

        axes[1].set_xlabel('Time (h)')
        axes[0].set_ylabel('mRNA (molecules)')
        axes[1].set_ylabel('Protein (molecules)')

        return fig

    def plot_average_trajectory(self, t, m, n):
        """ Plot the average of multiple trajectories
        Args:
            t (:obj:`numpy.array`): simulation time (h)
            m (:obj:`numpy.array`): predicted mRNA (molecules)
            n (:obj:`numpy.array`): predicted proteins (molecules)
        Return:
            :obj:`matplotlib.figure.Figure`: figure
        """

        m_percentiles = numpy.zeros((t.size, 7))
        n_percentiles = numpy.zeros((t.size, 7))
        for i, _ in enumerate(t):
            m_percentiles[i, :] = [
                numpy.percentile(m[i, :], 1),
                numpy.percentile(m[i, :], 5),
                numpy.percentile(m[i, :], 33.33),
                numpy.percentile(m[i, :], 50),
                numpy.percentile(m[i, :], 66.67),
                numpy.percentile(m[i, :], 95),
                numpy.percentile(m[i, :], 99),
            ]
            n_percentiles[i, :] = [
                numpy.percentile(n[i, :], 1),
                numpy.percentile(n[i, :], 5),
                numpy.percentile(n[i, :], 33.33),
                numpy.percentile(n[i, :], 50),
                numpy.percentile(n[i, :], 66.67),
                numpy.percentile(n[i, :], 95),
                numpy.percentile(n[i, :], 99),
            ]

        fig, axes = pyplot.subplots(nrows=2, ncols=1)

        axes[0].plot(t, m_percentiles[:, 1], label=r'$-2 \sigma$')
        axes[0].plot(t, m_percentiles[:, 2], label=r'$-1 \sigma$')
        axes[0].plot(t, m_percentiles[:, 3], label=r'$0 \sigma$')
        axes[0].plot(t, m_percentiles[:, 4], label=r'$1 \sigma$')
        axes[0].plot(t, m_percentiles[:, 5], label=r'$2 \sigma$')

        axes[1].plot(t, n_percentiles[:, 1], label=r'$-2 \sigma$')
        axes[1].plot(t, n_percentiles[:, 2], label=r'$-1 \sigma$')
        axes[1].plot(t, n_percentiles[:, 3], label=r'$0 \sigma$')
        axes[1].plot(t, n_percentiles[:, 4], label=r'$1 \sigma$')
        axes[1].plot(t, n_percentiles[:, 5], label=r'$2 \sigma$')

        axes[0].legend()

        axes[0].set_xlim((t[0], t[-1]))
        axes[1].set_xlim((t[0], t[-1]))

        axes[0].set_ylim([0, numpy.max(m) + 1])
        axes[1].set_ylim([numpy.min(n) - 5, numpy.max(n) + 5])

        axes[1].set_xlabel('Time (h)')
        axes[0].set_ylabel('mRNA (molecules)')
        axes[1].set_ylabel('Protein (molecules)')

        return fig

    def plot_mrna_protein_distribution(self, m, n):
        """ Plot the average of multiple trajectories
        Args:
            m (:obj:`numpy.array`): predicted mRNA (molecules)
            n (:obj:`numpy.array`): predicted proteins (molecules)
        Return:
            :obj:`matplotlib.figure.Figure`: figure
        """
        fig, axes = pyplot.subplots(nrows=2, ncols=1)

        kernel_m = stats.gaussian_kde(m.flatten())
        kernel_n = stats.gaussian_kde(n.flatten())
        m = range(int(numpy.min(m)), int(numpy.max(m)) + 1)
        n = range(int(numpy.min(n)), int(numpy.max(n)) + 1)
        p_m = kernel_m(m).T
        p_n = kernel_n(n).T
        p_m = p_m / numpy.sum(p_m)
        p_n = p_n / numpy.sum(p_n)

        axes[0].plot(m, p_m)
        axes[1].plot(n, p_n)

        axes[0].set_xlim((m[0], m[-1]))
        axes[1].set_xlim((n[0], n[-1]))

        axes[0].set_xlabel('mRNA (molecules)')
        axes[1].set_xlabel('Protein (molecules)')

        axes[0].set_ylabel('PDF')
        axes[1].set_ylabel('PDF')

        return fig


def trajectory_exercise():
    sim = SsaSimulation()

    ##########################################################
    # Implement SSA
    ##########################################################
    sim.simulate

    ##########################################################
    # Simulate one trajectory
    ##########################################################
    # seed random number generator
    numpy.random.seed(0)

    # simulate
    t, m, n = sim.simulate_ensemble(1, t_end=5., t_step=0.001)

    # plot
    fig = sim.plot_trajectories(t, m, n)
    # fig.show()
    filename = os.path.join(OUT_DIR, 'mrna-and-protein-using-several-methods-trajectory-simulation.png')
    fig.savefig(filename, transparent=True, bbox_inches='tight')
    pyplot.close(fig)

    ##########################################################
    # Simulate several trajectories
    ##########################################################
    # simulate
    n_trajectories = 50
    t, m, n = sim.simulate_ensemble(n_trajectories, t_end=2., t_step=0.2)

    # plot
    fig = sim.plot_trajectories(t, m, n)
    # fig.show()
    filename = os.path.join(OUT_DIR, 'mrna-and-protein-using-several-methods-trajectory-simulations.png')
    fig.savefig(filename, transparent=True, bbox_inches='tight')
    pyplot.close(fig)

    ##########################################################
    # Plot the average of multiple trajectories
    ##########################################################
    fig = sim.plot_average_trajectory(t, m, n)
    # fig.show()
    filename = os.path.join(OUT_DIR, 'mrna-and-protein-using-several-methods-trajectory-average.png')
    fig.savefig(filename, transparent=True, bbox_inches='tight')
    pyplot.close(fig)

    fig = sim.plot_mrna_protein_distribution(m, n)
    # fig.show()
    filename = os.path.join(OUT_DIR, 'mrna-and-protein-using-several-methods-trajectory-histogram.png')
    fig.savefig(filename, transparent=True, bbox_inches='tight')
    pyplot.close(fig)


if __name__ == '__main__':
    trajectory_exercise()