# My Drogon App

A modern C++ web application built with the Drogon framework, featuring user management with PostgreSQL database integration.

## 🚀 Features

- **User Management**: Sign up and retrieve users
- **RESTful API**: Clean API endpoints with JSON responses
- **PostgreSQL Integration**: Robust database operations with ORM
- **Docker Support**: Easy containerized deployment
- **Modern C++**: Built with C++17 standards

## 📋 Prerequisites

Before you begin, ensure you have the following installed:

- **C++17 compatible compiler** (GCC 7+, Clang 5+, or MSVC 2017+)
- **CMake** (version 3.5 or higher)
- **Drogon Framework** (latest version)
- **PostgreSQL** (or use Docker)
- **Docker & Docker Compose** (optional, for containerized setup)

### Installing Drogon Framework

```bash
# Clone Drogon repository
git clone https://github.com/drogonframework/drogon.git
cd drogon

# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
make -j$(nproc)

# Install (requires sudo)
sudo make install
```

## 🛠️ Installation & Setup

### Option 1: Using Docker (Recommended)

1. **Clone the repository**
   ```bash
   git clone <your-repo-url>
   cd my-drogon-app
   ```

2. **Start PostgreSQL with Docker**
   ```bash
   docker-compose up -d
   ```

3. **Build the application**
   ```bash
   mkdir build && cd build
   cmake ..
   make -j$(nproc)
   ```

4. **Run the application**
   ```bash
   ./my_drogon_app
   ```

### Option 2: Local PostgreSQL Setup

1. **Install PostgreSQL**
   ```bash
   # Ubuntu/Debian
   sudo apt-get install postgresql postgresql-contrib
   
   # macOS
   brew install postgresql
   ```

2. **Setup Database**
   ```bash
   # Create database and user
   sudo -u postgres psql
   CREATE DATABASE userdb;
   CREATE USER postgres WITH PASSWORD 'postgres';
   GRANT ALL PRIVILEGES ON DATABASE userdb TO postgres;
   \q
   
   # Initialize tables
   psql -h localhost -U postgres -d userdb -f init.sql
   ```

3. **Build and Run**
   ```bash
   mkdir build && cd build
   cmake ..
   make -j$(nproc)
   ./my_drogon_app
   ```

## 📁 Project Structure

```
my-drogon-app/
├── CMakeLists.txt
├── config.json
├── main.cc
├── init.sql
├── docker-compose.yml
├── Dockerfile
├── setup.md
├── README.md
├── controllers/
│   ├── api_v1_User.h
│   └── api_v1_User.cc
├── models/
│   ├── model.json
│   ├── Users.h
│   └── Users.cc
├── utils/
│   ├── AppError.h
│   ├── AppError.cc
│   ├── token.h
│   └── token.cc
├── filters/
│   ├── auth.h
│   └── auth.cc
├── dependencies/
│   ├── jwt-cpp/
│   │   └── include/
│   │       ├── jwt-cpp/
│   │       └── picojson/
│   └── Bcrypt/
│       ├── include/
│       │   └── bcrypt.h
│       └── src/
│           ├── bcrypt.cpp
│           ├── blowfish.cpp
│           ├── node_blf.h
│           └── openbsd.h
├── uploads/
│   └── tmp/
│       ├── FB/
│       ├── FC/
│       ├── ... (many more subfolders)
├── build/
│   ├── my_drogon_app
│   └── ... (build artifacts)
└── .vscode/
    └── settings.json
```

### Notes
- The `dependencies/` folder contains third-party libraries used by the project, such as JWT-CPP for JWT handling and Bcrypt for password hashing.
- The `filters/` folder contains authentication filters.
- The `utils/` folder contains utility classes and functions, such as error handling and token utilities.
- The `uploads/tmp/` folder contains many subdirectories for temporary file storage (all currently empty, used for sharding or temp files).
- The `.vscode/` folder contains editor configuration for development.

## 🔧 Configuration

### Application Configuration (`config.json`)

```json
{
    "listeners": [
      {
        "address": "0.0.0.0",
        "port": 3000
      }
    ],
    "db_clients": [
      {
        "rdbms": "postgresql",
        "host": "127.0.0.1",
        "port": 8000,
        "dbname": "userdb",
        "user": "postgres",
        "password": "postgres",
        "is_fast": false
      }
    ]
}
```

### Database Configuration

- **Host**: 127.0.0.1 (or localhost)
- **Port**: 8000 (Docker) or 5432 (local PostgreSQL)
- **Database**: userdb
- **Username**: postgres
- **Password**: postgres

## 📚 API Documentation

### Base URL
```
http://localhost:3000/api/v1/User
```

### Endpoints

#### 1. User Signup
**POST** `/api/v1/User/signup`

Creates a new user account.

**Request Body:**
```json
{
    "name": "John Doe",
    "email": "john@example.com",
    "password": "securepassword123"
}
```

**Success Response (201):**
```json
{
    "id": 1,
    "name": "John Doe",
    "email": "john@example.com",
    "password": "securepassword123"
}
```

**Error Response (400):**
```json
{
    "message": "All fields are required",
    "success": false
}
```

#### 2. Get All Users
**GET** `/api/v1/User/getUsers`

Retrieves all registered users.

**Success Response (200):**
```json
[
    {
        "id": 1,
        "name": "John Doe",
        "email": "john@example.com",
        "password": "securepassword123"
    },
    {
        "id": 2,
        "name": "Jane Smith",
        "email": "jane@example.com",
        "password": "anotherpassword"
    }
]
```

**Error Response (500):**
```json
{
    "message": "Database error message",
    "success": false
}
```

## 🗄️ Database Schema

### Users Table
```sql
CREATE TABLE users (
    id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    email VARCHAR(255) UNIQUE NOT NULL,
    password VARCHAR(255) NOT NULL
);
```

## 🧪 Testing the API

### Using curl

1. **Create a new user:**
   ```bash
   curl -X POST http://localhost:3000/api/v1/User/signup \
     -H "Content-Type: application/json" \
     -d '{
       "name": "Test User",
       "email": "test@example.com",
       "password": "testpassword"
     }'
   ```

2. **Get all users:**
   ```bash
   curl -X GET http://localhost:3000/api/v1/User/getUsers
   ```

### Using Postman

1. Import the following collection:
   ```json
   {
     "info": {
       "name": "My Drogon App API",
       "schema": "https://schema.getpostman.com/json/collection/v2.1.0/collection.json"
     },
     "item": [
       {
         "name": "User Signup",
         "request": {
           "method": "POST",
           "header": [
             {
               "key": "Content-Type",
               "value": "application/json"
             }
           ],
           "body": {
             "mode": "raw",
             "raw": "{\n  \"name\": \"Test User\",\n  \"email\": \"test@example.com\",\n  \"password\": \"testpassword\"\n}"
           },
           "url": {
             "raw": "http://localhost:3000/api/v1/User/signup",
             "protocol": "http",
             "host": ["localhost"],
             "port": "3000",
             "path": ["api", "v1", "User", "signup"]
           }
         }
       },
       {
         "name": "Get All Users",
         "request": {
           "method": "GET",
           "url": {
             "raw": "http://localhost:3000/api/v1/User/getUsers",
             "protocol": "http",
             "host": ["localhost"],
             "port": "3000",
             "path": ["api", "v1", "User", "getUsers"]
           }
         }
       }
     ]
   }
   ```

## 🔄 Development Workflow

### Adding New Endpoints

1. **Update Controller Header** (`controllers/api_v1_User.h`):
   ```cpp
   METHOD_ADD(User::newMethod, "/newEndpoint", Post);
   void newMethod(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback);
   ```

2. **Implement Controller Method** (`controllers/api_v1_User.cc`):
   ```cpp
   void User::newMethod(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) {
       // Implementation here
   }
   ```

3. **Rebuild and Test**:
   ```bash
   cd build
   make -j$(nproc)
   ./my_drogon_app
   ```

### Database Model Changes

1. **Update `models/model.json`** with new table definitions
2. **Generate new model files**:
   ```bash
   drogon_ctl create model -c models/model.json
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