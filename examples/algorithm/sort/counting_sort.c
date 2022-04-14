// COUNTING-SORT I O k
// 1 let C[0....K] be a new array
// 2 for i = 0 to k
// 3    C[I[i]] += 1 // C[i] now contains the number of elements equal to i .
// 4 
// 5 for i = 1 to k
// 6    C[i] = C[i] + C[i-1]
// 7 // C[i] now is the (index+1) in the sorted array of last same i [0,(0),1,2,2] C: [2, 3, 5]
// 8 for j = O.length downto 1
// 9    O[C[I[j]] - 1] = I[j]
//10    C[I[j]]-- 