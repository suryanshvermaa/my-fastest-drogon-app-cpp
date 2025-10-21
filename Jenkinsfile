pipeline{
    agent any
    parameters{
        string(name: 'BACKEND_DOCKER_TAG',defaultValue:'',description:'setting docker image for latest push')
    }
    stages{
        stage("Validate parameters"){
            steps{
                script{
                    if(params.BACKEND_DOCKER_TAG==''){
                        error("Backend Docker tag is missing")
                    }
                }
            }
        }
        stage("Workspace Cleanup"){
            steps{
                script{
                    cleanWs()
                }
            }
        }
        stage("cloning"){
            steps{
                echo "cloning code..."
                git url: 'https://github.com/suryanshvermaa/my-fastest-drogon-app-cpp.git',branch: 'main'
                echo "cloning code successful."
            }
        }
        stage("building"){
            steps{
                echo "building code..."
                sh "docker build -t my-app ."
                echo "building code successful."
            }
        }
        stage("pushing code to dockerhub..."){
            steps{
                echo "pushing code to dockerhub..."
                withCredentials([usernamePassword(credentialsId:"dockerhubCredentials",passwordVariable:"dockerPass",usernameVariable:"dockerUser")]){
                    sh "docker login -u ${env.dockerUser} -p ${env.dockerPass}"
                    sh "docker tag my-app ${env.dockerUser}/drogon-app:${params.BACKEND_DOCKER_TAG}"
                    sh "docker push ${env.dockerUser}/drogon-app:${params.BACKEND_DOCKER_TAG}"
                    echo "pushing to dockerhub successful."
                }
            }
        }
        stage("changing k8s-deployment tag"){
            steps{
                script{
                    dir("./k8/app"){
                        sh "sed -i 's|image: suryanshvermaa/drogon-app.*|image: suryanshvermaa/drogon-app:${parms.BACKEND_DOCKER_TAG}|' deployment.yaml"
                    }
                }
            }
        }
        stage("pushing to github"){
            steps{
                script{
                    echo "pushing to github..."
                    withCredentials([gitUsernamePassword(credentialsId:'Github-Cred',gitToolName:'Default')]){
                        sh "git add ."
                        sh "git commit -m \"updated k8s-deployment image tag\""
                        sh "git push origin main"
                        echo "pushing to github successfully."
                    }
                    echo "deployment done."
                }
            }
        }
    }
}