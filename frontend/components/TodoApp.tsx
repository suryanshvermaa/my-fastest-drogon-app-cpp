"use client"

import { useState, useEffect } from "react"
import { Header } from "./Header"
import { ProgressCard } from "./ProgressCard"
import { AddTodoForm } from "./AddTodoForm"
import { TodoFilters } from "./TodoFilters"
import { TodoList } from "./TodoList"
import { LoadingSpinner } from "./ui/LoadingSpinner"
import { todoApi } from "@/lib/api"
import type { Todo, FilterType } from "@/types/todo"
import axios from "axios"

export function TodoApp() {
  const [todos, setTodos] = useState<Todo[]>([])
  const [loading, setLoading] = useState(true)
  const [filter, setFilter] = useState<FilterType>("all")
  const [searchTerm, setSearchTerm] = useState("")

  useEffect(() => {
    loadTodos()
  }, [])

  const loadTodos = async () => {
    try {
      setLoading(true)
      const res=await axios.get("http://localhost:3001/api/v1/todos/getAll",{
        headers:{
          Authorization:`Bearer ${localStorage.getItem("token")}`
        }
      });
      setTodos(res.data.data);
    } catch (error) {
      console.error("Failed to load todos:", error)
    } finally {
      setLoading(false)
    }
  }

  const addTodo = async (title: string) => {
    try {
      const newTodo = await axios.post("http://localhost:3001/api/v1/todos/create",{title,completed:false},{
        headers:{
          Authorization:`Bearer ${localStorage.getItem("token")}`
        }
      });
      setTodos((prev) => [newTodo.data.data, ...prev]);
    } catch (error) {
      console.error("Failed to create todo:", error)
    }
  }

  const updateTodo = async (id: number, updates: Partial<Todo>) => {
    try {
      await axios.put(`http://localhost:3001/api/v1/todos/update/${id}`,{title:updates.title||todos.find((todo)=>todo.id=id)?.title,completed:updates.completed||todos.find((todo)=>todo.id=id)?.completed},{
        headers:{
          Authorization:`Bearer ${localStorage.getItem("token")}`
        }
      });
      setTodos((prev) => prev.map((todo) => (todo.id === id ? { ...todo, ...updates } : todo)))
    } catch (error) {
      console.error("Failed to update todo:", error)
    }
  }

  const deleteTodo = async (id: number) => {
    try {
      await axios.delete(`http://localhost:3001/api/v1/todos/delete/${id}`,{
        headers:{
          Authorization:`Bearer ${localStorage.getItem("token")}`
        }
      });
      setTodos((prev) => prev.filter((todo) => todo.id !== id))
    } catch (error) {
      console.error("Failed to delete todo:", error)
    }
  }

  const filteredTodos = todos.filter((todo) => {
    const matchesFilter =
      filter === "all" || (filter === "active" && !todo.completed) || (filter === "completed" && todo.completed)
    const matchesSearch = todo.title.toLowerCase().includes(searchTerm.toLowerCase())
    return matchesFilter && matchesSearch
  })

  const completedCount = todos.filter((todo) => todo.completed).length
  const totalCount = todos.length

  if (loading) {
    return <LoadingSpinner />
  }

  return (
    <div className="min-h-screen bg-gradient-to-br from-slate-50 via-blue-50 to-indigo-100">
      <Header completedCount={completedCount} totalCount={totalCount} />

      <main className="max-w-5xl mx-auto px-4 sm:px-6 lg:px-8 py-8">
        <div className="space-y-6">
          <ProgressCard completedCount={completedCount} totalCount={totalCount} />
          <AddTodoForm onAddTodo={addTodo} />
          <TodoFilters
            filter={filter}
            onFilterChange={setFilter}
            searchTerm={searchTerm}
            onSearchChange={setSearchTerm}
          />
          <TodoList todos={filteredTodos} onUpdateTodo={updateTodo} onDeleteTodo={deleteTodo} searchTerm={searchTerm} />
        </div>
      </main>
    </div>
  )
}
