"use client"

import type React from "react"

import { useState } from "react"
import { Plus } from "lucide-react"
import { Button } from "./ui/Button"
import { Input } from "./ui/Input"

interface AddTodoFormProps {
  onAddTodo: (title: string) => Promise<void>
}

export function AddTodoForm({ onAddTodo }: AddTodoFormProps) {
  const [title, setTitle] = useState("")
  const [isSubmitting, setIsSubmitting] = useState(false)

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault()
    if (!title.trim() || isSubmitting) return

    try {
      setIsSubmitting(true)
      await onAddTodo(title.trim())
      setTitle("")
    } finally {
      setIsSubmitting(false)
    }
  }

  return (
    <div className="bg-white/90 backdrop-blur-sm rounded-2xl p-6 shadow-lg border border-white/30">
      <form onSubmit={handleSubmit} className="flex gap-4">
        <div className="flex-1">
          <Input
            value={title}
            onChange={(e) => setTitle(e.target.value)}
            placeholder="What needs to be done today?"
            className="text-lg h-12"
            disabled={isSubmitting}
          />
        </div>
        <Button type="submit" size="lg" disabled={!title.trim() || isSubmitting} className="px-8 h-12">
          <Plus className="h-5 w-5 mr-2" />
          {isSubmitting ? "Adding..." : "Add Task"}
        </Button>
      </form>
    </div>
  )
}
