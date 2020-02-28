((nil
  . ((eval
      . (progn
          (setq-local flycheck-clang-include-path (list (concat (projectile-project-root) "include")))
          (setq-local flycheck-gcc-include-path flycheck-clang-include-path)
          )
      ))
  ))
