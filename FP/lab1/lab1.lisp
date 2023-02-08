(defun iter (n a b c i)
	(cond
		((< n i) a)
		(t (iter n (* a (+ b 2) (+ c 3)) a b (+ i 1))) 
	)
)
(defun laba (n)
	(iter n 1 1 1 3)
)