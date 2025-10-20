# Drogon C++ Todo Application

[![C++](https://img.shields.io/badge/C++-20-blue.svg)](https://isocpp.org/)
[![Drogon](https://img.shields.io/badge/Drogon-v1.9.0-green.svg)](https://github.com/drogonframework/drogon)
[![PostgreSQL](https://img.shields.io/badge/PostgreSQL-15-blue.svg)](https://www.postgresql.org/)
[![Next.js](https://img.shields.io/badge/Next.js-15.2-black.svg)](https://nextjs.org/)
[![Docker](https://img.shields.io/badge/Docker-Enabled-2496ED.svg)](https://www.docker.com/)
[![Kubernetes](https://img.shields.io/badge/Kubernetes-Ready-326CE5.svg)](https://kubernetes.io/)

A high-performance, production-ready full-stack Todo application built with **Drogon C++ Framework** for the backend, **Next.js 15** for the frontend, and **PostgreSQL** as the database. Features include JWT authentication, RESTful API, Docker containerization, and Kubernetes deployment with CI/CD pipeline.

## 📑 Table of Contents

- [Features](#-features)
- [Tech Stack](#-tech-stack)
- [Architecture](#-architecture)
- [Prerequisites](#-prerequisites)
- [Installation & Setup](#️-installation--setup)
  - [Docker Setup (Recommended)](#option-1-docker-setup-recommended)
  - [Local Development](#option-2-local-development)
- [API Documentation](#-api-documentation)
- [Deployment](#-deployment)
- [Project Structure](#-project-structure)
- [Contributing](#-contributing)
- [License](#-license)

## ✨ Features

### Backend (Drogon C++)
- 🚀 **High-Performance**: Built with Drogon, one of the fastest C++ web frameworks
- 🔐 **JWT Authentication**: Secure token-based authentication with bcrypt password hashing
- 📝 **CRUD Operations**: Complete Todo management (Create, Read, Update, Delete)
- 🗄️ **PostgreSQL Integration**: Robust ORM support with Drogon's built-in mapper
- 🛡️ **Custom Middleware**: Authentication filters and error handling
- 🌐 **CORS Support**: Pre-configured CORS for frontend integration
- 🏥 **Health Check**: Built-in health monitoring endpoint
- 📦 **Docker Ready**: Multi-stage builds for optimized production images

### Frontend (Next.js)
- ⚡ **Next.js 15**: Latest React framework with Turbopack
- 🎨 **Modern UI**: Tailwind CSS with Radix UI components
- 🔄 **Real-time Updates**: Seamless todo management interface
- 🎯 **Type-Safe**: Full TypeScript implementation
- 📱 **Responsive Design**: Mobile-first approach

### DevOps & Infrastructure
- 🐳 **Docker & Docker Compose**: Containerized development and production
- ☸️ **Kubernetes Ready**: Complete K8s manifests with Ingress
- 🔄 **CI/CD Pipeline**: Jenkins integration with automated builds
- 📊 **ArgoCD**: GitOps-based continuous deployment
- 🔒 **Secrets Management**: Kubernetes secrets for sensitive data

## 🛠️ Tech Stack

### Backend
- **Framework**: Drogon v1.9.0 (C++20)
- **Database**: PostgreSQL 15
- **Authentication**: JWT-CPP, Bcrypt.cpp
- **ORM**: Drogon ORM
- **Build System**: CMake 3.5+

### Frontend
- **Framework**: Next.js 15.2.4
- **Language**: TypeScript 5
- **Styling**: Tailwind CSS 4
- **UI Components**: Radix UI, Lucide Icons
- **HTTP Client**: Axios

### DevOps
- **Containerization**: Docker, Docker Compose
- **Orchestration**: Kubernetes
- **CI/CD**: Jenkins, ArgoCD
- **Ingress**: NGINX Ingress Controller

## 🏗️ Architecture

```
┌─────────────┐         ┌──────────────┐         ┌──────────────┐
│   Next.js   │────────▶│  Drogon C++  │────────▶│  PostgreSQL  │
│  Frontend   │  HTTP   │   Backend    │   ORM   │   Database   │
│  (Port 3000)│         │  (Port 3001) │         │  (Port 5432) │
└─────────────┘         └──────────────┘         └──────────────┘
       │                        │
       │                        │
       ▼                        ▼
┌─────────────┐         ┌──────────────┐
│    Docker   │         │  Kubernetes  │
│   Compose   │         │   Cluster    │
└─────────────┘         └──────────────┘
```

## 📋 Prerequisites

### For Docker Setup (Recommended)
- **Docker** (20.10+)
- **Docker Compose** (v3.8+)

### For Local Development
- **C++20 compatible compiler** (GCC 10+, Clang 10+, or MSVC 2019+)
- **CMake** (3.5 or higher)
- **PostgreSQL** (15+)
- **Node.js** (20+) and npm/yarn
- **Git**

### For Kubernetes Deployment
- **kubectl**
- **Kubernetes cluster** (minikube, kind, or cloud provider)
- **NGINX Ingress Controller**
- **ArgoCD** (optional, for GitOps)

## 🛠️ Installation & Setup

### Option 1: Docker Setup (Recommended)

1. **Clone the repository**
   ```bash
   git clone https://github.com/suryanshvermaa/my-fastest-drogon-app-cpp.git
   cd my-fastest-drogon-app-cpp
   ```

2. **Start PostgreSQL database**
   ```bash
   docker-compose up -d postgres
   ```
   This will start PostgreSQL on port 5432 and automatically run `init.sql` to create tables.

3. **Build and run the backend**
   
   **Option A: Using Docker (Production)**
   ```bash
   docker build -t drogon-app:latest -f Dockerfile .
   docker run -p 3001:3001 --network host drogon-app:latest
   ```

   **Option B: Build locally**
   ```bash
   # Install dependencies
   bash dependencies.sh
   
   # Build
   mkdir -p build && cd build
   cmake .. -DCMAKE_BUILD_TYPE=Release
   make -j$(nproc)
   
   # Run
   ./my_drogon_app
   ```

4. **Setup and run the frontend** (in a new terminal)
   ```bash
   cd frontend
   npm install
   npm run dev
   ```

5. **Access the application**
   - Frontend: http://localhost:3000
   - Backend API: http://localhost:3001/api/v1
   - Health Check: http://localhost:3001/api/v1/health/

### Option 2: Local Development

#### Backend Setup

1. **Install Drogon Framework**
   ```bash
   # Clone and build Drogon
   git clone https://github.com/drogonframework/drogon.git
   cd drogon
   git checkout v1.9.0
   git submodule update --init --recursive
   
   mkdir build && cd build
   cmake .. -DCMAKE_BUILD_TYPE=Release
   make -j$(nproc)
   sudo make install
   sudo ldconfig
   ```

2. **Install PostgreSQL**
   ```bash
   # Ubuntu/Debian
   sudo apt-get update
   sudo apt-get install postgresql postgresql-contrib libpq-dev
   
   # macOS
   brew install postgresql@15
   brew services start postgresql@15
   ```

3. **Setup Database**
   ```bash
   # Start PostgreSQL service
   sudo service postgresql start  # Linux
   # or
   brew services start postgresql@15  # macOS
   
   # Create database
   sudo -u postgres psql -c "CREATE DATABASE userdb;"
   sudo -u postgres psql -c "ALTER USER postgres WITH PASSWORD 'postgres';"
   
   # Initialize tables
   psql -h localhost -U postgres -d userdb -f init.sql
   ```

4. **Build and run the application**
   ```bash
   # Install dependencies
   bash dependencies.sh
   
   # Configure and build
   mkdir -p build && cd build
   cmake .. -DCMAKE_BUILD_TYPE=Debug
   make -j$(nproc)
   
   # Run
   ./my_drogon_app
   ```

#### Frontend Setup

```bash
cd frontend
npm install
npm run dev
```

## 📁 Project Structure

```
my-fastest-drogon-app-cpp/
├── 📂 src/                          # Backend source code
│   ├── main.cc                      # Application entry point with CORS
│   ├── 📂 controllers/              # API controllers
│   │   ├── api_v1_User.{cc,h}      # User authentication (signup/login/profile)
│   │   ├── api_v1_todos.{cc,h}     # Todo CRUD operations
│   │   └── api_v1_health.{cc,h}    # Health check endpoint
│   ├── 📂 models/                   # Database models (ORM)
│   │   ├── Users.{cc,h}            # User model
│   │   ├── Todos.{cc,h}            # Todo model
│   │   └── model.json              # Drogon model configuration
│   ├── 📂 filters/                  # Middleware filters
│   │   ├── auth.{cc,h}             # JWT authentication filter
│   │   └── CorsMiddleware.{cc,h}   # CORS middleware
│   └── 📂 utils/                    # Utility functions
│       ├── token.{cc,h}            # JWT token management
│       └── AppError.{cc,h}         # Custom error handling
│
├── 📂 frontend/                     # Next.js frontend
│   ├── 📂 app/                      # Next.js app directory
│   │   ├── page.tsx                # Main todo page
│   │   ├── layout.tsx              # Root layout
│   │   ├── globals.css             # Global styles
│   │   └── 📂 auth/                # Authentication pages
│   ├── 📂 components/               # React components
│   │   ├── TodoApp.tsx             # Main todo app
│   │   ├── TodoList.tsx            # Todo list display
│   │   ├── TodoItem.tsx            # Individual todo item
│   │   ├── AddTodoForm.tsx         # Add todo form
│   │   ├── LoginPage.tsx           # Login component
│   │   ├── SignUpPage.tsx          # Signup component
│   │   └── 📂 ui/                  # Reusable UI components
│   ├── 📂 lib/                      # Utilities
│   │   ├── api.ts                  # API client
│   │   └── utils.ts                # Helper functions
│   ├── 📂 types/                    # TypeScript types
│   └── package.json
│
├── 📂 k8s/                          # Kubernetes manifests
│   ├── namespace.yaml              # K8s namespace
│   ├── ingress.yaml                # Ingress configuration
│   ├── 📂 app/                      # Backend deployment
│   │   ├── deployment.yaml         # App deployment
│   │   ├── svc.yaml                # App service
│   │   └── secret.yaml             # App secrets
│   ├── 📂 db/                       # Database deployment
│   │   ├── deployment.yaml         # DB deployment
│   │   ├── svc.yaml                # DB service
│   │   ├── pv.yaml                 # Persistent volume
│   │   ├── pvc.yaml                # PV claim
│   │   └── secrets.yaml            # DB secrets
│   ├── argocd_installation.sh      # ArgoCD setup script
│   ├── jenkins_installation.sh     # Jenkins setup script
│   └── *.md                        # K8s documentation
│
├── 📂 dependencies/                 # Third-party C++ libraries
│   ├── 📂 jwt-cpp/                 # JWT library
│   └── 📂 Bcrypt/                  # Bcrypt library
│
├── 📂 scripts/                      # Utility scripts
│   └── dev-entrypoint.sh           # Docker dev entrypoint
│
├── CMakeLists.txt                  # CMake build configuration
├── config.json                     # Local development config
├── config.docker.json              # Docker config
├── init.sql                        # Database initialization
├── dependencies.sh                 # Dependency installation script
├── docker-compose.yml              # Docker Compose config
├── Dockerfile                      # Production Docker image
├── Dockerfile.dev                  # Development Docker image
├── Jenkinsfile                     # CI/CD pipeline
└── README.md                       # This file
```

## 🔧 Configuration

### Backend Configuration

The application supports two configuration files:

**`config.json`** (Local development):
```json
{
  "listeners": [
    {
      "address": "0.0.0.0",
      "port": 3001
    }
  ],
  "db_clients": [
    {
      "rdbms": "postgresql",
      "host": "127.0.0.1",
      "port": 5432,
      "dbname": "userdb",
      "user": "postgres",
      "password": "postgres",
      "is_fast": false
    }
  ]
}
```

**`config.docker.json`** (Docker environment):
```json
{
  "listeners": [
    {
      "address": "0.0.0.0",
      "port": 3001
    }
  ],
  "db_clients": [
    {
      "rdbms": "postgresql",
      "host": "postgres",
      "port": 5432,
      "dbname": "userdb",
      "user": "postgres",
      "password": "postgres",
      "is_fast": false
    }
  ]
}
```

### Environment Variables

Set the following environment variable for JWT authentication:

```bash
export JWT_SECRET="your-secret-key-here"
```

For Docker/Kubernetes, this is configured via secrets.

## 📚 API Documentation

### Base URL
```
http://localhost:3001/api/v1
```

### Authentication

The API uses JWT (JSON Web Tokens) for authentication. Protected endpoints require an `Authorization` header:

```
Authorization: Bearer <your-jwt-token>
```

### Endpoints

#### 🔐 Authentication Endpoints

##### **POST** `/api/v1/User/signup`
Create a new user account.

**Request Body:**
```json
{
  "name": "John Doe",
  "email": "john@example.com",
  "password": "securepassword"
}
```

**Response:** `201 Created`
```json
{
  "status": "success",
  "token": "eyJhbGciOiJIUzI1NiIs...",
  "user": {
    "id": 1,
    "name": "John Doe",
    "email": "john@example.com"
  }
}
```

##### **POST** `/api/v1/User/login`
Login to an existing account.

**Request Body:**
```json
{
  "email": "john@example.com",
  "password": "securepassword"
}
```

**Response:** `200 OK`
```json
{
  "status": "success",
  "token": "eyJhbGciOiJIUzI1NiIs...",
  "user": {
    "id": 1,
    "name": "John Doe",
    "email": "john@example.com"
  }
}
```

##### **GET** `/api/v1/User/profile` 🔒
Get current user profile (requires authentication).

**Headers:**
```
Authorization: Bearer <token>
```

**Response:** `200 OK`
```json
{
  "id": 1,
  "name": "John Doe",
  "email": "john@example.com",
  "created_at": "2025-01-15T10:30:00Z"
}
```

---

#### ✅ Todo Endpoints (All require authentication)

##### **POST** `/api/v1/todos/create` 🔒
Create a new todo.

**Request Body:**
```json
{
  "title": "Complete project documentation",
  "completed": false
}
```

**Response:** `201 Created`
```json
{
  "id": 1,
  "user_id": 1,
  "title": "Complete project documentation",
  "completed": false,
  "created_at": "2025-01-15T10:30:00Z"
}
```

##### **GET** `/api/v1/todos/getAll` 🔒
Get all todos for the authenticated user.

**Response:** `200 OK`
```json
[
  {
    "id": 1,
    "title": "Complete project documentation",
    "completed": false,
    "created_at": "2025-01-15T10:30:00Z"
  },
  {
    "id": 2,
    "title": "Review pull requests",
    "completed": true,
    "created_at": "2025-01-15T11:00:00Z"
  }
]
```

##### **GET** `/api/v1/todos/{id}` 🔒
Get a specific todo by ID.

**Response:** `200 OK`
```json
{
  "id": 1,
  "title": "Complete project documentation",
  "completed": false,
  "user_id": 1
}
```

##### **GET** `/api/v1/todos/getAll/{completion}` 🔒
Get todos filtered by completion status.

**Parameters:**
- `completion`: `true` or `false`

**Example:** `/api/v1/todos/getAll/true`

##### **PUT** `/api/v1/todos/update/{id}` 🔒
Update a todo.

**Request Body:**
```json
{
  "title": "Updated title",
  "completed": true
}
```

**Response:** `200 OK`
```json
{
  "id": 1,
  "title": "Updated title",
  "completed": true,
  "updated_at": "2025-01-15T12:00:00Z"
}
```

##### **DELETE** `/api/v1/todos/delete/{id}` 🔒
Delete a todo.

**Response:** `200 OK`
```json
{
  "status": "success",
  "message": "Todo deleted successfully"
}
```

---

#### 🏥 Health Check

##### **GET** `/api/v1/health`
Check API health status.

**Response:** `200 OK`
```json
{
  "status": "healthy",
  "timestamp": "2025-01-15T10:30:00Z"
}
```

## 🗄️ Database Schema

### Entity Relationship Diagram

```
┌─────────────────────┐
│      users          │
├─────────────────────┤
│ id (PK)             │
│ name                │
│ email (UNIQUE)      │
│ password (hashed)   │
│ created_at          │
│ updated_at          │
└──────────┬──────────┘
           │ 1
           │
           │ N
┌──────────▼──────────┐
│      todos          │
├─────────────────────┤
│ id (PK)             │
│ user_id (FK)        │
│ title               │
│ completed           │
│ created_at          │
│ updated_at          │
└─────────────────────┘
```

### Table Definitions

#### Users Table
```sql
CREATE TABLE users (
    id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    email VARCHAR(255) UNIQUE NOT NULL,
    password VARCHAR(255) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
```

#### Todos Table
```sql
CREATE TABLE todos(
    id SERIAL PRIMARY KEY,
    user_id INTEGER NOT NULL REFERENCES users(id) ON DELETE CASCADE,
    title VARCHAR(255) NOT NULL,
    completed BOOLEAN DEFAULT FALSE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
```

### Relationships
- **Users → Todos**: One-to-Many (One user can have multiple todos)
- **ON DELETE CASCADE**: When a user is deleted, all their todos are automatically deleted

## 🧪 Testing the API

### Using cURL

1. **Signup**
   ```bash
   curl -X POST http://localhost:3001/api/v1/User/signup \
     -H "Content-Type: application/json" \
     -d '{
       "name": "Test User",
       "email": "test@example.com",
       "password": "password123"
     }'
   ```

2. **Login**
   ```bash
   curl -X POST http://localhost:3001/api/v1/User/login \
     -H "Content-Type: application/json" \
     -d '{
       "email": "test@example.com",
       "password": "password123"
     }'
   ```

3. **Get Profile** (save token from login response)
   ```bash
   TOKEN="your-jwt-token-here"
   curl -X GET http://localhost:3001/api/v1/User/profile \
     -H "Authorization: Bearer $TOKEN"
   ```

4. **Create Todo**
   ```bash
   curl -X POST http://localhost:3001/api/v1/todos/create \
     -H "Content-Type: application/json" \
     -H "Authorization: Bearer $TOKEN" \
     -d '{
       "title": "Learn Drogon Framework",
       "completed": false
     }'
   ```

5. **Get All Todos**
   ```bash
   curl -X GET http://localhost:3001/api/v1/todos/getAll \
     -H "Authorization: Bearer $TOKEN"
   ```

6. **Update Todo**
   ```bash
   curl -X PUT http://localhost:3001/api/v1/todos/update/1 \
     -H "Content-Type: application/json" \
     -H "Authorization: Bearer $TOKEN" \
     -d '{
       "title": "Learn Drogon Framework",
       "completed": true
     }'
   ```

7. **Delete Todo**
   ```bash
   curl -X DELETE http://localhost:3001/api/v1/todos/delete/1 \
     -H "Authorization: Bearer $TOKEN"
   ```

## � Deployment

### Docker Deployment

#### Production Build
```bash
# Build production image
docker build -t drogon-app:latest -f Dockerfile .

# Run with docker-compose
docker-compose up -d
```

#### Development Build
```bash
# Build dev image with hot-reload support
docker build -t drogon-app:dev -f Dockerfile.dev .

# Run development container
docker run -it --rm \
  -v $(pwd):/app \
  -p 3001:3001 \
  --network host \
  drogon-app:dev
```

### Kubernetes Deployment

1. **Create namespace**
   ```bash
   kubectl apply -f k8s/namespace.yaml
   ```

2. **Deploy PostgreSQL database**
   ```bash
   kubectl apply -f k8s/db/
   ```

3. **Deploy application**
   ```bash
   kubectl apply -f k8s/app/
   ```

4. **Setup Ingress**
   ```bash
   # Install NGINX Ingress Controller (if not already installed)
   kubectl apply -f https://raw.githubusercontent.com/kubernetes/ingress-nginx/controller-v1.8.2/deploy/static/provider/cloud/deploy.yaml
   
   # Apply ingress rules
   kubectl apply -f k8s/ingress.yaml
   ```

5. **Verify deployment**
   ```bash
   kubectl get pods -n drogon-project
   kubectl get svc -n drogon-project
   kubectl get ingress -n drogon-project
   ```

### CI/CD with Jenkins

The project includes a `Jenkinsfile` for automated CI/CD:

**Pipeline Stages:**
1. **Workspace Cleanup**: Clean previous builds
2. **Clone Repository**: Fetch latest code
3. **Build Docker Image**: Build production image
4. **Push to Docker Hub**: Push image to registry
5. **Update K8s Deployment**: Update deployment manifest
6. **Git Commit**: Commit changes for GitOps

**Setup:**
1. Configure Jenkins credentials:
   - `dockerhubCredentials`: Docker Hub username/password
   - `Github-Cred`: GitHub credentials

2. Create Jenkins pipeline job:
   ```bash
   # Point to Jenkinsfile in repository
   # Configure parameter: BACKEND_DOCKER_TAG
   ```

3. Trigger build:
   ```bash
   # Manual trigger with tag parameter
   # Or webhook-based automatic trigger
   ```

### ArgoCD GitOps Deployment

1. **Install ArgoCD**
   ```bash
   bash k8s/argocd_installation.sh
   ```

2. **Create ArgoCD Application**
   ```bash
   kubectl apply -f - <<EOF
   apiVersion: argoproj.io/v1alpha1
   kind: Application
   metadata:
     name: drogon-app
     namespace: argocd
   spec:
     project: default
     source:
       repoURL: https://github.com/suryanshvermaa/my-fastest-drogon-app-cpp
       targetRevision: main
       path: k8s
     destination:
       server: https://kubernetes.default.svc
       namespace: drogon-project
     syncPolicy:
       automated:
         prune: true
         selfHeal: true
   EOF
   ```

3. **Access ArgoCD UI**
   ```bash
   kubectl port-forward svc/argocd-server -n argocd 8080:443
   # Open: https://localhost:8080
   ```

## 🔄 Development Workflow

### Adding New API Endpoints

1. **Define route in controller header** (`src/controllers/api_v1_User.h`):
   ```cpp
   METHOD_ADD(User::newEndpoint, "/newPath", Post, "auth");
   void newEndpoint(const HttpRequestPtr& req, 
                    std::function<void (const HttpResponsePtr &)> &&callback);
   ```

2. **Implement method** (`src/controllers/api_v1_User.cc`):
   ```cpp
   void User::newEndpoint(const HttpRequestPtr& req, 
                          std::function<void (const HttpResponsePtr &)> &&callback) {
       try {
           auto json = req->getJsonObject();
           // Your logic here
           
           Json::Value response;
           response["status"] = "success";
           auto resp = HttpResponse::newHttpJsonResponse(response);
           callback(resp);
       } catch (const std::exception &e) {
           auto resp = HttpResponse::newHttpResponse();
           resp->setStatusCode(k500InternalServerError);
           resp->setBody(e.what());
           callback(resp);
       }
   }
   ```

3. **Rebuild and test**:
   ```bash
   cd build
   make -j$(nproc)
   ./my_drogon_app
   ```

### Creating New Database Models

1. **Update database schema** (`init.sql`):
   ```sql
   CREATE TABLE new_table (
       id SERIAL PRIMARY KEY,
       field1 VARCHAR(255) NOT NULL,
       created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
   );
   ```

2. **Update model configuration** (`src/models/model.json`):
   ```json
   {
     "tables": ["users", "todos", "new_table"]
   }
   ```

3. **Generate model classes**:
   ```bash
   drogon_ctl create model src/models/model.json
   ```

4. **Update CMakeLists.txt**:
   ```cmake
   add_executable(${PROJECT_NAME}
       src/models/NewTable.cc
       # ... other files
   )
   ```

### Hot Reload Development

For development with automatic rebuild:

```bash
# Use the dev entrypoint script
docker-compose -f docker-compose.dev.yml up

# Or use file watchers
while inotifywait -r -e modify,create,delete src/; do
    cd build && make -j$(nproc) && ./my_drogon_app
done
```
3. **Update database schema** in `init.sql`
4. **Rebuild the application**

## 🐛 Troubleshooting

### Common Issues

1. **Port Already in Use**
   ```bash
   # Find process using port 3000
   sudo lsof -i :3000
   
   # Kill the process
   sudo kill -9 <PID>
   ```

2. **Database Connection Failed**
   - Ensure PostgreSQL is running
   - Check database credentials in `config.json`
   - Verify database exists: `psql -h localhost -U postgres -d userdb`

3. **Build Errors**
   - Ensure Drogon is properly installed
   - Check CMake version: `cmake --version`
   - Verify C++17 support: `g++ --version`

4. **Docker Issues**
   ```bash
   # Reset Docker containers
   docker-compose down -v
   docker-compose up -d
   ```

### Logs

- **Application logs**: Check console output when running the app
- **Database logs**: `docker logs postgres_container` (if using Docker)
- **System logs**: `journalctl -u postgresql` (if using system PostgreSQL)

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch: `git checkout -b feature-name`
3. Make your changes
4. Test thoroughly
5. Commit your changes: `git commit -m 'Add feature'`
6. Push to the branch: `git push origin feature-name`
7. Submit a pull request

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- [Drogon Framework](https://github.com/drogonframework/drogon) - The C++ web framework
- [PostgreSQL](https://www.postgresql.org/) - The database system
- [Docker](https://www.docker.com/) - Containerization platform

## 📞 Support

For support and questions:
- Create an issue in the repository
- Check the [Drogon documentation](https://drogon.docsforge.com/)
- Review the [PostgreSQL documentation](https://www.postgresql.org/docs/)

---

**Happy Coding! 🚀** 