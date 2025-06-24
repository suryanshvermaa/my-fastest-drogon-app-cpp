import { CheckCircle2 } from "lucide-react"
import { TodoItem } from "./TodoItem"
import type { Todo } from "@/types/todo"

interface TodoListProps {
  todos: Todo[]
  onUpdateTodo: (id: number, updates: Partial<Todo>) => Promise<void>
  onDeleteTodo: (id: number) => Promise<void>
  searchTerm: string
}

export function TodoList({ todos, onUpdateTodo, onDeleteTodo, searchTerm }: TodoListProps) {
  if (todos.length === 0) {
    return (
      <div className="bg-white/90 backdrop-blur-sm rounded-2xl shadow-lg border border-white/30 overflow-hidden">
        <div className="p-12 text-center">
          <div className="w-16 h-16 bg-gray-100 rounded-full flex items-center justify-center mx-auto mb-4">
            <CheckCircle2 className="h-8 w-8 text-gray-400" />
          </div>
          <h3 className="text-lg font-medium text-gray-900 mb-2">
            {searchTerm ? "No matching tasks" : "No tasks yet"}
          </h3>
          <p className="text-gray-600">
            {searchTerm
              ? "Try adjusting your search or filter criteria"
              : "Add your first task above to get started with your productivity journey"}
          </p>
        </div>
      </div>
    )
  }

  return (
    <div className="bg-white/90 backdrop-blur-sm rounded-2xl shadow-lg border border-white/30 overflow-hidden">
      <div className="divide-y divide-gray-100">
        {todos.map((todo) => (
          <TodoItem key={todo.id} todo={todo} onUpdate={onUpdateTodo} onDelete={onDeleteTodo} />
        ))}
      </div>
    </div>
  )
}
