(defun reverse-tree (x)
        (cond
                ;; Для атома
                ((and (atom (first x)) (not (null (first x)))) (first x) (reverse-tree (rest x)))
                ;; Для подсписка
                ((not (atom (first x))) (list (reverse-tree (rest x)) (reverse-tree (first x))))
        )
)