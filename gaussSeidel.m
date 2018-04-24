function x = gaussSeidel(A, x0, b, maxError = 1.0e-3, maxIterations = 1000)
	#format long PRECISA COLOCAR NA HORA DE PRINTAR

	x = x0;	
	xNew = x;
	err = maxError + 1;
	l = 0;
	n = size(A, 1)
	while(l < maxIterations && err > maxError)

		for i = 1:n
			aux1 = dot(A(i,:), xNew, i-1);
			aux2 = dot(A(i,i+1:n), xNew(i+1:n));
			xNew(i) = (b(i) - aux1(i) - aux2(i))./A(i,i);
		endfor

		# Calcular o erro Norma Infinita
		err = norm(xNew - x, OPT=inf);
		x = xNew;
		i++;
	endwhile

	return
endfunction