interface ProgressCardProps {
  completedCount: number
  totalCount: number
}

export function ProgressCard({ completedCount, totalCount }: ProgressCardProps) {
  const progressPercentage = totalCount > 0 ? (completedCount / totalCount) * 100 : 0

  return (
    <div className="bg-white/90 backdrop-blur-sm rounded-2xl p-6 shadow-lg border border-white/30">
      <div className="flex items-center justify-between mb-4">
        <h2 className="text-lg font-semibold text-gray-900">Today's Progress</h2>
        <div className="text-3xl font-bold bg-gradient-to-r from-blue-600 to-purple-600 bg-clip-text text-transparent">
          {Math.round(progressPercentage)}%
        </div>
      </div>

      <div className="w-full bg-gray-200 rounded-full h-4 mb-4 overflow-hidden">
        <div
          className="bg-gradient-to-r from-blue-600 to-purple-600 h-4 rounded-full transition-all duration-700 ease-out shadow-sm"
          style={{ width: `${progressPercentage}%` }}
        />
      </div>

      <div className="flex justify-between text-sm text-gray-600">
        <span className="flex items-center">
          <div className="w-2 h-2 bg-green-500 rounded-full mr-2" />
          {completedCount} tasks completed
        </span>
        <span className="flex items-center">
          <div className="w-2 h-2 bg-orange-500 rounded-full mr-2" />
          {totalCount - completedCount} remaining
        </span>
      </div>
    </div>
  )
}
