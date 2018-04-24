function A = pentadiag(n)
	A = zeros(n) + diag(ones(n, 1) * 4);

	for i = [-1, 1, -3, 3]
		A -= diag(ones(n-abs(i), 1), i);
	endfor

	return 
endfunction