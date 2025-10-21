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
- **Docker Compose** (2.0+)

### For Local Development
- **C++20 compiler** (GCC 10+/Clang 10+/MSVC 2019+)
- **CMake** (3.5+)
- **PostgreSQL** (15+)
- **Drogon Framework** (v1.9.0)
- **Node.js** (20+) - only if working on the frontend

## 📁 Project Structure

```
my-fastest-drogon-app-cpp/
├── CMakeLists.txt
├── config.json
├── config.docker.json
├── Dockerfile            # production (multi-stage)
├── Dockerfile.dev        # development image with entrypoint
├── docker-compose.yml    # postgres service (API optional)
├── db.dockerfile         # builds DB image seeded with init.sql
├── init.sql              # DB schema (users, todos)
├── Jenkinsfile           # CI pipeline: build, push, retag k8s, push changes
├── scripts/
│   └── dev-entrypoint.sh
├── src/
│   ├── main.cc
│   ├── controllers/
│   │   ├── api_v1_User.{h,cc}
│   │   ├── api_v1_todos.{h,cc}
│   │   └── api_v1_health.{h,cc}
│   ├── filters/
│   │   ├── auth.{h,cc}
│   │   └── CorsMiddleware.{h,cc}
│   ├── models/
│   │   ├── Users.{h,cc}
│   │   ├── Todos.{h,cc}
│   │   └── model.json
│   └── utils/
│       ├── AppError.{h,cc}
│       └── token.{h,cc}
├── k8s/
│   ├── namespace.yaml
│   ├── ingress.yaml
│   ├── app/
│   │   ├── deployment.yaml
│   │   ├── secret.yaml
│   │   └── svc.yaml
│   └── db/
│       ├── deployment.yaml
│       ├── pv.yaml
│       ├── pvc.yaml
│       ├── secrets.yaml
│       └── svc.yaml
└── dependencies/         # vendored jwt-cpp, Bcrypt (used via CMake)
```

*Note: Folders `build/`, `pgdata/`, `uploads/` excluded. Frontend has its own README in `frontend/`.*

## ⚙️ Configuration

Two configs are provided; Drogon auto-loads `config.json` from the working directory.

- `config.json` (local): connects to `127.0.0.1:5432`
- `config.docker.json` (containers): connects to service `postgres`

Example (local `config.json`):

```json
{
  "listeners": [{ "address": "0.0.0.0", "port": 3001 }],
  "db_clients": [{
    "rdbms": "postgresql",
    "host": "127.0.0.1",
    "port": 5432,
    "dbname": "userdb",
    "user": "postgres",
    "password": "postgres",
    "is_fast": false
  }]
}
```

JWT secret (required by `src/utils/token.cc`):
- **Local/dev**: set environment variable `JWT_SECRET`
- **Kubernetes**: provided through `k8s/app/secret.yaml` (key: `jwt_secret`)

## 🚀 Installation & Setup

### Option 1: Docker Setup (Recommended)

1. **Start PostgreSQL with Docker Compose**
   ```powershell
   docker-compose up -d postgres
   ```

2. **Build and run the application**
   ```powershell
   docker build -t drogon-app:latest -f Dockerfile .
   docker run --rm -p 3001:3001 -e JWT_SECRET=your-secret-key drogon-app:latest
   ```

### Option 2: Local Development

1. **Install Drogon** (build from source v1.9.0 as shown in `setup.md`)

2. **Build the application**
   ```powershell
   mkdir build
   cd build
   cmake .. -DCMAKE_BUILD_TYPE=Debug
   cmake --build . -j
   ```

3. **Setup database and run**
   ```powershell
   # Ensure PostgreSQL is running and load the schema
   psql -h 127.0.0.1 -U postgres -d userdb -f ../init.sql
   
   # Set JWT secret and run
   $Env:JWT_SECRET="your-secret-key-here"
   .\my_drogon_app.exe
   ```

   Backend will read `config.json` and listen on port 3001.

## 📡 API Documentation

**Base URL**: `http://localhost:3001/api/v1`

### Authentication Endpoints
- **POST** `/User/signup` — Register (name, email, password) → returns JWT
- **POST** `/User/login` — Login (email, password) → returns JWT
- **GET** `/User/profile` — Get user profile (requires `Authorization: Bearer <token>`)

### Todo Endpoints (All require JWT authentication)
- **POST** `/todos/create` — Create todo `{ title, completed }`
- **GET** `/todos/getAll` — List all todos for authenticated user
- **GET** `/todos/{id}` — Get single todo by ID
- **GET** `/todos/getAll/{completion}` — Filter todos by completion status (true/false)
- **PUT** `/todos/update/{id}` — Update todo `{ title, completed }`
- **DELETE** `/todos/delete/{id}` — Delete todo

### Health Check
- **GET** `/health/` — Service status

*CORS is handled globally in `src/main.cc` and via `CorsMiddleware`.*

## 🚢 Deployment

### Kubernetes Deployment

1. **Create namespace**
   ```powershell
   kubectl apply -f k8s/namespace.yaml
   ```

2. **Deploy PostgreSQL database**
   ```powershell
   kubectl apply -f k8s/db/
   ```

3. **Deploy application**
   ```powershell
   kubectl apply -f k8s/app/
   ```

4. **Setup Ingress**
   ```powershell
   kubectl apply -f k8s/ingress.yaml
   ```

5. **Verify deployment**
   ```powershell
   kubectl get pods -n drogon-project
   kubectl get svc -n drogon-project
   kubectl get ingress -n drogon-project
   ```

### CI/CD Pipeline

**Jenkins Pipeline** (`Jenkinsfile`):
1. Validates parameters (requires `BACKEND_DOCKER_TAG`)
2. Cleans workspace and clones repository
3. Builds Docker image and pushes to Docker Hub (requires `dockerhubCredentials`)
4. Updates `k8s/app/deployment.yaml` image tag
5. Commits changes back to repository (requires `Github-Cred`)

**ArgoCD**: Helper scripts and documentation in `k8s/` for GitOps-style continuous deployment.

## 🔧 Development Notes

- `src/utils/token.cc` reads `JWT_SECRET` from environment variable
- ORM models are mapped in `src/models/*.cc` and `model.json` (tables: users, todos)
- `src/filters/auth.*` injects `userId` and `email` into request parameters after JWT validation
- `init.sql` creates `users` and `todos` tables with foreign keys and timestamps

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
   ```powershell
   cd build
   cmake --build . -j
   .\my_drogon_app.exe
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
   ```powershell
   drogon_ctl create model src/models/model.json
   ```

4. **Update CMakeLists.txt** to include the new model source files and rebuild

## 🐛 Troubleshooting

### Common Issues

1. **Port Already in Use**
   ```powershell
   # Find and stop the process using port 3001
   Get-Process -Id (Get-NetTCPConnection -LocalPort 3001).OwningProcess | Stop-Process
   ```

2. **Database Connection Failed**
   - Ensure PostgreSQL is running
   - Check database credentials in `config.json`
   - Verify database exists: `psql -h localhost -U postgres -d userdb`

3. **Build Errors**
   - Ensure Drogon is properly installed
   - Check CMake version: `cmake --version`
   - Verify C++20 compiler support

4. **Docker Issues**
   ```powershell
   # Reset Docker containers
   docker-compose down -v
   docker-compose up -d
   ```

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch: `git checkout -b feature-name`
3. Make your changes and test thoroughly
4. Commit: `git commit -m 'Add feature'`
5. Push: `git push origin feature-name`
6. Submit a pull request

## 📄 License

MIT License © 2025 Suryansh Verma - see [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- [Drogon Framework](https://github.com/drogonframework/drogon) - High-performance C++ web framework
- [PostgreSQL](https://www.postgresql.org/) - Robust database system
- [JWT-CPP](https://github.com/Thalhammer/jwt-cpp) - JWT token library
- [BCrypt](https://github.com/hilch/Bcrypt.cpp) - Password hashing

---

**Built with ❤️ using C++20 and Drogon Framework**
 