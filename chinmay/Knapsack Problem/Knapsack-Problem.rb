# Implementing Knapsack Problem 

val = []
weight = []

 puts "Input value array:"
 for i in 0..19
 	j = gets.chomp
 	val << j.to_i
 end

 puts "Input weight array:"
 for i in 0..19
 	j = gets.chomp	
 	weight << j.to_i
 end

 puts "Input weight of the Knapsack"
 w = 40

 n = val.length

 knap = Array.new(n+1){ Array.new(w+1) }

for i in 0..n
	for j in 0..w
		if i==0 or w==0
			knap[i][j] = 0
		elsif weight[i-1] <= j
			knap[i][j] = [val[i-1] + knap[i-1][j-weight[i-1]], knap[i-1][j]].max
		else
			knap[i][j] = knap[i-1][j]
		end
	end
end

puts knap[n][w]
