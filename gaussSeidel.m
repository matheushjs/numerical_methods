function x = gaussSeidel(A, x0, b, maxError = 1.0e-6, maxIterations = 10000)
	#format long PRECISA COLOCAR NA HORA DE PRINTAR

	x = xNew = x0;		
	n = size(A, 1);	
	err = maxError + 1;
	aux1 = aux2 = zeros(1, n);		
	l = 0;

	while(l < maxIterations && err > maxError)
		for i = 1:n			
			if (i > 1)
				aux1(i) = dot(A(i, 1:i-1), xNew(1:i-1));
			else
				aux1(i) = 0;
			endif
			aux2(i) = dot(A(i,i+1:n), xNew(i+1:n));
			xNew(i) = (b(i) - aux1(i) - aux2(i))./A(i,i);
		endfor

		# Calcular o erro Norma Infinita
		err = norm(xNew - x, OPT=inf);
		x = xNew;
		i++;
	endwhile

	return;
endfunction