pipeline {
    agent any

    options {
        timestamps()
    }

    stages {
        stage('Pobranie kodu') {
            steps {
                checkout scm
                sh '''
                    mkdir -p reports
                    echo "=== Informacje o repozytorium ===" | tee reports/repository.txt
                    git remote -v | tee -a reports/repository.txt
                    git log -1 --oneline | tee -a reports/repository.txt
                '''
            }
        }

        stage('Wersje narzedzi') {
            steps {
                sh '''
                    echo "=== Wersje narzedzi ===" | tee reports/tools-versions.txt

                    echo "\\nGCC:" | tee -a reports/tools-versions.txt
                    gcc --version | head -n 1 | tee -a reports/tools-versions.txt

                    echo "\\nCPPCheck:" | tee -a reports/tools-versions.txt
                    cppcheck --version | tee -a reports/tools-versions.txt

                    echo "\\nClang:" | tee -a reports/tools-versions.txt
                    clang --version | head -n 1 | tee -a reports/tools-versions.txt

                    echo "\\nClang-tidy:" | tee -a reports/tools-versions.txt
                    clang-tidy --version | head -n 1 | tee -a reports/tools-versions.txt || true

                    echo "\\nSplint:" | tee -a reports/tools-versions.txt
                    splint -help | head -n 3 | tee -a reports/tools-versions.txt || true
                '''
            }
        }

        stage('GCC - kompilacja z warningami') {
            steps {
                sh '''
                    echo "=== GCC warnings ===" | tee reports/gcc-warnings.txt

                    gcc -std=c11 \
                        -Wall \
                        -Wextra \
                        -Wpedantic \
                        -Wconversion \
                        -Wshadow \
                        -Werror \
                        -o sort sort.c \
                        2>&1 | tee -a reports/gcc-warnings.txt
                '''
            }
        }

        stage('Uruchomienie programu') {
            steps {
                sh '''
                    echo "=== Wynik programu ===" | tee reports/program-output.txt
                    ./sort 2>&1 | tee -a reports/program-output.txt
                '''
            }
        }

        stage('cppcheck') {
            steps {
                sh '''
                    echo "=== cppcheck ===" | tee reports/cppcheck.txt

                    cppcheck \
                        --enable=all \
                        --inconclusive \
                        --std=c11 \
                        --language=c \
                        --suppress=missingIncludeSystem \
                        --error-exitcode=1 \
                        sort.c \
                        2>&1 | tee -a reports/cppcheck.txt
                '''
            }
        }

        stage('clang-tidy') {
            steps {
                sh '''
                    echo "=== clang-tidy ===" | tee reports/clang-tidy.txt

                    clang-tidy sort.c -checks='clang-analyzer-*,bugprone-*,readability-*,performance-*' -- -std=c11 \
                        2>&1 | tee -a reports/clang-tidy.txt
                '''
            }
        }

        stage('Clang Static Analyzer') {
            steps {
                sh '''
                    echo "=== clang --analyze ===" | tee reports/clang-analyzer.txt

                    clang \
                        --analyze \
                        -std=c11 \
                        -Wall \
                        -Wextra \
                        sort.c \
                        2>&1 | tee -a reports/clang-analyzer.txt
                '''
            }
        }

        stage('splint') {
            steps {
                sh '''
                    echo "=== splint ===" | tee reports/splint.txt

                    splint \
                        +posixlib \
                        -weak \
                        sort.c \
                        2>&1 | tee -a reports/splint.txt || true
                '''
            }
        }

        stage('cppcheck MISRA') {
            steps {
                sh '''
                    echo "=== cppcheck MISRA ===" | tee reports/cppcheck-misra.txt

                    cppcheck \
                        --addon=misra \
                        --std=c11 \
                        --language=c \
                        --suppress=missingIncludeSystem \
                        sort.c \
                        2>&1 | tee -a reports/cppcheck-misra.txt || true
                '''
            }
        }
    }

    post {
        always {
            archiveArtifacts artifacts: 'reports/**', allowEmptyArchive: true
        }

        success {
            echo 'Pipeline zakonczony powodzeniem. Wykonano kompilacje, uruchomienie programu oraz analize statyczna.'
        }

        failure {
            echo 'Pipeline zakonczony bledem. Sprawdz Console Output i raporty w artifacts/reports.'
        }
    }
}
