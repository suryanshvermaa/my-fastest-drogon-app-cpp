"use client"

import { useState } from "react"
import { Check, X, Edit3, Trash2, CheckCircle2, Circle } from "lucide-react"
import { Button } from "./ui/Button"
import { Input } from "./ui/Input"
import type { Todo } from "@/types/todo"

interface TodoItemProps {
  todo: Todo
  onUpdate: (id: number, updates: Partial<Todo>) => Promise<void>
  onDelete: (id: number) => Promise<void>
}

export function TodoItem({ todo, onUpdate, onDelete }: TodoItemProps) {
  const [isEditing, setIsEditing] = useState(false)
  const [editTitle, setEditTitle] = useState(todo.title)
  const [isUpdating, setIsUpdating] = useState(false)

  const handleToggleComplete = async () => {
    if (isUpdating) return
    setIsUpdating(true)
    try {
      await onUpdate(todo.id, { completed: !todo.completed })
    } finally {
      setIsUpdating(false)
    }
  }

  const handleStartEdit = () => {
    setIsEditing(true)
    setEditTitle(todo.title)
  }

  const handleSaveEdit = async () => {
    if (!editTitle.trim()) return
    try {
      await onUpdate(todo.id, { title: editTitle.trim() })
      setIsEditing(false)
    } catch (error) {
      console.error("Failed to update todo:", error)
    }
  }

  const handleCancelEdit = () => {
    setIsEditing(false)
    setEditTitle(todo.title)
  }

  const handleDelete = async () => {
    try {
      await onDelete(todo.id)
    } catch (error) {
      console.error("Failed to delete todo:", error)
    }
  }

  return (
    <div className={`p-6 transition-all duration-200 hover:bg-gray-50/50 ${todo.completed ? "opacity-75" : ""}`}>
      <div className="flex items-center space-x-4">
        <button
          onClick={handleToggleComplete}
          disabled={isUpdating}
          className="flex-shrink-0 transition-all duration-200 hover:scale-110 disabled:opacity-50"
        >
          {todo.completed ? (
            <CheckCircle2 className="h-6 w-6 text-green-600" />
          ) : (
            <Circle className="h-6 w-6 text-gray-400 hover:text-blue-600" />
          )}
        </button>

        {isEditing ? (
          <div className="flex-1 flex items-center space-x-3">
            <Input
              value={editTitle}
              onChange={(e) => setEditTitle(e.target.value)}
              onKeyDown={(e) => {
                if (e.key === "Enter") handleSaveEdit()
                if (e.key === "Escape") handleCancelEdit()
              }}
              autoFocus
              className="flex-1"
            />
            <Button
              onClick={handleSaveEdit}
              variant="ghost"
              size="sm"
              className="text-green-600 hover:text-green-700 hover:bg-green-50"
            >
              <Check className="h-4 w-4" />
            </Button>
            <Button onClick={handleCancelEdit} variant="ghost" size="sm" className="text-gray-500 hover:text-gray-700">
              <X className="h-4 w-4" />
            </Button>
          </div>
        ) : (
          <>
            <div className="flex-1">
              <p className={`text-lg ${todo.completed ? "line-through text-gray-500" : "text-gray-900"}`}>
                {todo.title}
              </p>
            </div>

            <div className="flex items-center space-x-2">
              <Button
                onClick={handleStartEdit}
                variant="ghost"
                size="sm"
                className="text-blue-600 hover:text-blue-700 hover:bg-blue-50"
              >
                <Edit3 className="h-4 w-4" />
              </Button>
              <Button
                onClick={handleDelete}
                variant="ghost"
                size="sm"
                className="text-red-600 hover:text-red-700 hover:bg-red-50"
              >
                <Trash2 className="h-4 w-4" />
              </Button>
            </div>
          </>
        )}
      </div>
    </div>
  )
}
