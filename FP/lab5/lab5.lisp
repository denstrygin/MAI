(defun make-term (&key order coeff)
    (list order coeff)
)

(defun order (term) (first term))   ; степень
(defun coeff (term) (second term))  ; коэффициент

(defclass polynom ()
    (
        (var-symbol :initarg :vars :reader vars)
        ;; Разреженный список термов в порядке убывания степени
        (term-list :initarg :terms :reader terms)
    )
)

(defgeneric zerop1 (arg)
    (:method ((n number))   ; (= n 0)
        (zerop n)
    )
)

(defgeneric minusp1 (arg)
    (:method ((n number))   ; (< n 0)
        (minusp n)
    )
)

(defmethod print-object ((p polynom) stream)
    (format stream "[МЧ (~s) ~:{~:[~:[+~;-~]~d~[~2*~;~s~*~:;~s^~d~]~;~]~}]"
        (vars p)
        (mapcar (lambda (term)
                    (list (zerop1 (coeff term))
                        (minusp1 (coeff term))
                        (if (minusp1 (coeff term))
                            (abs (coeff term))
                            (coeff term)
                        )
                        (order term)
                        (vars p)
                        (order term)
                    )
                )
            (terms p)
        )
    )
)

;;; Удаляю первый терм из списка
(defmethod delterm ((p polynom))
    (make-instance 'polynom
        :vars (vars p)
        :terms (rest (terms p))
    )
)

;;; Рекурсивно обрабатываю список термов
(defmethod term-list ((n number) (p polynom))
    (if (null (second (terms p)))
        (list (list (first (first (terms p))) (* n (second (first (terms p))))))
        (append (list (list (first (first (terms p))) (* n (second (first (terms p)))))) (term-list n (delterm p)))
    )
)

;;; Метод, создающий экземпляр класс полином и возвращающий его в качестве ответа
(defmethod mul2 ((n number) (p polynom))
    (make-instance 'polynom
        :vars (vars p)
        :terms (term-list n p)
    )
)

(defvar p1)
(setq p1 (make-instance 'polynom ; 5x^2 + 3.3x - 7
    :vars 'x
    :terms (list (make-term :order 2 :coeff 5)
        (make-term :order 1 :coeff 3.3)
        (make-term :order 0 :coeff -7)))
)
(defvar p2)
(setq p2 (make-instance 'polynom ; 5x^2 + 3.3x - 7
    :vars 'x
    :terms (list (make-term :order 3 :coeff 1)
        (make-term :order 2 :coeff 5)
        (make-term :order 1 :coeff 3.3)
        (make-term :order 0 :coeff -7)))
)