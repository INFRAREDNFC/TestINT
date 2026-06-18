pipeline {
    agent any

    stages {
        stage('Pobranie kodu') {
            steps {
                checkout scm
                sh 'git --version'
                sh 'git log -1 --oneline'
            }
        }

        stage('Kompilacja') {
            steps {
                sh 'make clean all'
            }
        }

        stage('Uruchomienie programu') {
            steps {
                sh './sort'
            }
        }
    }

    post {
        success {
            echo 'Pipeline zakonczony powodzeniem - projekt pobrany, skompilowany i uruchomiony.'
        }
        failure {
            echo 'Pipeline zakonczony bledem - sprawdz Console Output.'
        }
    }
}
