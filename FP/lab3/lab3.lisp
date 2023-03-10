(defun print-matrix (matrix &optional (chars 3) stream)
  (let ((*print-right-margin* (+ 6 (* (1+ chars)
                                      (array-dimension matrix 1)))))
    (pprint matrix stream)
    (values)))
(eval-when (:compile-toplevel :load-toplevel :execute)
 (defun open-bracket-reader (stream char)
   (declare (ignore char))
   (cons 'aref (read-delimited-list #\] stream t)))

 (set-macro-character #\[ #'open-bracket-reader)
 (set-macro-character #\] (get-macro-character #\))) )

(defvar x (make-array '(3 3)
        :initial-contents '((1 2 3) (4 5 6) (7 8 9))))

(defun swap-max-to-top-left (x)
        (let ((maximum 0) (max_i 0) (max_j 0) (buf (make-array (list (array-dimension x 0) (array-dimension x 1)))))
                (loop with n = (array-dimension x 0)
                        for i upfrom 0 below n do
                                (loop with m = (array-dimension x 1)
                                        for j upfrom 0 below m do
                                                (setf [buf i j] [x i j])
                                                (when (> (ABS [x i j]) maximum) 
                                                        (setf maximum (ABS [x i j])) (setf max_i i) (setf max_j j)
                                                )
                                )
                )
                (loop with n = (array-dimension buf 0)
                        for i upfrom 0 below n do
                                (rotatef (aref buf i 0) (aref buf i max_j))
                )
                (when (> max_i 0)
                        (princ "Меняем метсами строки 0 и ")
                        (princ max_i)
                        (princ #\Newline)
                )
                (loop with n = (array-dimension buf 1)
                        for j upfrom 0 below n do
                                (rotatef (aref buf 0 j) (aref buf max_i j))
                )
                (when (> max_j 0)
                        (princ "Меняем местами столбцы 0 и ")
                        (princ max_j)
                )
                (print-matrix buf 1)
        )
)