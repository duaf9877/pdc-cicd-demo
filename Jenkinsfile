pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                checkout scm
                sh 'git log -1 --oneline'
            }
        }
        stage('Build') {
            steps {
                sh 'g++ -std=c++17 -fopenmp -O2 -o parallel_sum parallel_sum.cpp'
            }
        }
        stage('Test') {
            steps {
                sh 'OMP_NUM_THREADS=2 ./parallel_sum | tee test_output.txt'
                sh 'grep -q "TEST PASSED" test_output.txt'
            }
        }
        stage('Run') {
            steps {
                sh 'for t in 1 2; do echo "== $t thread(s) =="; OMP_NUM_THREADS=$t ./parallel_sum; done'
            }
        }
    }

    post {
        success { echo 'Pipeline finished successfully.' }
        failure { echo 'Pipeline failed. Check the stage logs.' }
    }
}
