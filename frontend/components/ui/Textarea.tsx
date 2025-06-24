import type { TextareaHTMLAttributes } from "react"

interface TextareaProps extends TextareaHTMLAttributes<HTMLTextAreaElement> {}

export function Textarea({ className = "", ...props }: TextareaProps) {
  return (
    <textarea
      className={`w-full px-4 py-3 bg-white border border-gray-200 rounded-xl focus:outline-none focus:ring-2 focus:ring-blue-500 focus:border-transparent transition-all duration-200 resize-none ${className}`}
      {...props}
    />
  )
}
