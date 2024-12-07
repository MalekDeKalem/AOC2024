import java.io.File

fun main() {
    val filePath = "input.txt"

    val col1 = mutableListOf<Int>()
    val col2 = mutableListOf<Int>()

    File(filePath).forEachLine { line ->
        if (line.isNotBlank()) {
            val parts = line.split("\\s+".toRegex())  
            if (parts.size == 2) {
                try {
                    val num1 = parts[0].toInt()
                    val num2 = parts[1].toInt()
                    col1.add(num1)
                    col2.add(num2)
                } catch (e: NumberFormatException) {
                    println("Skipping invalid line (could not parse numbers): $line")
                }
            } else {
                println("Skipping malformed line (not two numbers): $line")
            }
        }
    }

    if (col1.isNotEmpty() && col2.isNotEmpty()) {
        var nums1: IntArray = col1.toIntArray()
        var nums2: IntArray = col1.toIntArray()
        val res: Int = solution2(nums1, nums2)

        println("The solution is: $res")
    } else {
        println("No valid data to process.")
    }
}

fun solution1(list1: IntArray, list2: IntArray): Int {
    list1.sort()
    list2.sort()

    var sum = 0
    for (i in list1.indices) {
        val max = if (list1[i] >= list2[i]) list1[i] else list2[i]
        val min = if (list1[i] < list2[i]) list1[i] else list2[i]
        val diff = max - min
        sum += diff
    }

    return sum
}

fun solution2(list1: IntArray, list2: IntArray): Int {
    val countMap = mutableMapOf<Int, Int>()
    for (num in list2) {
        countMap[num] = countMap.getOrDefault(num, 0) + 1
    }

    var sum = 0
    for (num in list1) {
        val score = countMap.getOrDefault(num, 0)
        if (score > 0) {
            sum += (num * score)
        }
    }

    return sum
}
