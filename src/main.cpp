#include <mpi.h>
#include <iostream>
#include <random>
#include <vector>
#include "CStopWatch.h"

#include <boost/mpi.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>

namespace mpi = boost::mpi;

std::random_device rd;
std::mt19937 rng(rd());
std::uniform_real_distribution<double> myDist(-1, 1);
CStopWatch timer;
double pi = 0.0;

int calcPi(int nSamples) {

    double x, y;
    double estimate = 0.0;
    int numInCircle = 0.00;

    for(int i=0; i< nSamples; i++){
        x = myDist(rng);
        y = myDist(rng);

        if(x*x + y*y <=1){
            numInCircle++;
        }
    }

    return numInCircle;
}

void parallelPi(int n) {
    MPI_Status myStatus;
    mpi::communicator world;
    int procs, myRank;
    int localRes, res = 0.0;

    procs = world.size();
    myRank = world.rank();

    localRes = calcPi(n/procs);

    if (myRank != 0) {
        //worker process
        world.send(0, 0, localRes);
    }
    else {
        //master process
        res += localRes;
        for(int i = 1; i < procs; i++) {
            world.recv(i, 0, localRes);
            res += localRes;
        }
        pi = (4.0*res/((double) n));
    }
}

int main() {

    mpi::environment env;
    mpi::communicator world;
    double time = 0.0;

    int myRank = world.rank();
    int procs = world.size();

    for (int i = 0; i < 10; i++) {

        timer.startTimer();

        parallelPi(1000000000);

        timer.stopTimer();

        time += timer.getElapsedTime();
    }

    if (myRank == 0) {
        //TODO Add res and procs
        std::cout << procs << ',' << pi << ',' << time / 10.0 << '\n';
    }

    return 0;
}