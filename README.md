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
├── init.sql
├── docker-compose.yml
├── Dockerfile
├── setup.md
├── README.md
├── .gitignore
├── .dockerignore
├── src/
│   ├── main.cc
│   ├── controllers/
│   │   ├── api_v1_todos.cc
│   │   ├── api_v1_todos.h
│   │   ├── api_v1_User.cc
│   │   └── api_v1_User.h
│   ├── models/
│   │   ├── Todos.cc
│   │   ├── Todos.h
│   │   ├── Users.cc
│   │   ├── Users.h
│   │   └── model.json
│   ├── utils/
│   │   ├── AppError.cc
│   │   ├── AppError.h
│   │   ├── token.cc
│   │   └── token.h
│   └── filters/
│       ├── auth.cc
│       └── auth.h
├── .vscode/
│   └── settings.json
```

### Notes
- The `src/` folder contains all source code, organized into controllers, models, utils, and filters.
- The `.vscode/` folder contains editor configuration for development.
- The `.gitignore` and `.dockerignore` files specify files and folders to be ignored by Git and Docker, respectively.

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

### User Controller Endpoints

**Base URL:**
```
http://localhost:3000/api/v1/User
```

- **POST** `/api/v1/User/signup` — Create a new user
- **POST** `/api/v1/User/login` — Login a user
- **GET** `/api/v1/User/profile` — Get user profile (auth required)

### Todos Controller Endpoints

**Base URL:**
```
http://localhost:3000/api/v1/todos
```

- **GET** `/api/v1/todos/{id}` — Get a todo by ID
- **POST** `/api/v1/todos/create` — Create a new todo (auth required)
- **GET** `/api/v1/todos/getAll` — Get all todos (auth required)
- **GET** `/api/v1/todos/getAll/{completion}` — Get all todos by completion status (auth required)
- **PUT** `/api/v1/todos/update/{id}` — Update a todo by ID (auth required)
- **DELETE** `/api/v1/todos/delete/{id}` — Delete a todo by ID (auth required)

---

## 🗄️ Database Schema

### Users Table
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

### Todos Table
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

---

## 🗃️ Models

### Users Model
Represents a user in the system. Fields:
- `id`: integer, primary key
- `name`: string
- `email`: string, unique
- `password`: string
- `created_at`: timestamp
- `updated_at`: timestamp

### Todos Model
Represents a todo item. Fields:
- `id`: integer, primary key
- `user_id`: integer, references users(id)
- `title`: string
- `completed`: boolean
- `created_at`: timestamp
- `updated_at`: timestamp

---

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