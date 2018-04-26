% Função que implementa o Método Númerico Iterativo de Gauss-Seidel.
function x = gaussSeidel(A, x0, b, maxError = 1.0e-6, maxIterations = 10000)
	% Inicialização dos vetores de iteração.
	x = xNew = x0;		
	% Variável auxiliar da dimensão de A.
	n = size(A, 1);	
	% Inicialização do erro pré-iteração.
	err = maxError + 1;
	% Vetores auxiliares para o cálculo dos somatórios.
	prev = next = zeros(1, n);		
	% Variável contadora de iteração.
	k = 0;

	% Inicia as iterações do método numérico.
	while(k < maxIterations && err > maxError)
		% Calcula cada elemento de x(k+1).
		for i = 1:n						
			% Calcula o somatório utilizando os elementos anteriores de x(k+1).
			if (i > 1)
				prev(i) = dot(A(i, 1:i-1), xNew(1:i-1));
			else
				prev(i) = 0;
			endif
			% Calcula o somatório utilizando os elementos posteriores de x(k).
			next(i) = dot(A(i,i+1:n), xNew(i+1:n));

			% Atribui o valor na posição i do vetor x(k+1).
			xNew(i) = (b(i) - prev(i) - next(i))./A(i,i);
		endfor

		% Calcula o erro Norma Infinita.
		err = norm(xNew - x, OPT=inf);

		% Atribui o valor de x(k+1) como nova aproximação para x.
		x = xNew;

		% Incrementa o contador de iteração.
		k++;
	endwhile
	return;
endfunction