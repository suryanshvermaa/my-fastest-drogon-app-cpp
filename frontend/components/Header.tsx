import { CheckCircle2 } from "lucide-react"

interface HeaderProps {
  completedCount: number
  totalCount: number
}

export function Header({ completedCount, totalCount }: HeaderProps) {
  return (
    <header className="bg-white/90 backdrop-blur-sm border-b border-white/20 sticky top-0 z-50">
      <div className="max-w-5xl mx-auto px-4 sm:px-6 lg:px-8">
        <div className="flex items-center justify-between h-16">
          <div className="flex items-center space-x-4">
            <div className="w-10 h-10 bg-gradient-to-r from-blue-600 to-purple-600 rounded-xl flex items-center justify-center shadow-lg">
              <CheckCircle2 className="h-6 w-6 text-white" />
            </div>
            <div>
              <h1 className="text-xl font-bold text-gray-900">TaskFlow</h1>
              <p className="text-sm text-gray-600">Professional Task Management</p>
            </div>
          </div>

          <div className="flex items-center space-x-2 text-sm text-gray-600 bg-white/50 px-4 py-2 rounded-full">
            <span className="font-semibold text-blue-600">{completedCount}</span>
            <span>of</span>
            <span className="font-semibold text-gray-800">{totalCount}</span>
            <span>completed</span>
          </div>
        </div>
      </div>
    </header>
  )
}
