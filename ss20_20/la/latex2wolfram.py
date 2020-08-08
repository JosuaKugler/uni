latexmatrix = r"""\begin{pmatrix}
                    0 & 3 & 2 & 0\\
                    1 & 0 & 0 & 2\\
                    1 & 0 & 0 & 3\\
                    0 & 1 & 1 & 0
                \end{pmatrix}"""

latexmatrix = "".join(latexmatrix.split())
latexmatrix = latexmatrix.replace(r"\begin{pmatrix}", r"{{")
latexmatrix = latexmatrix.replace(r"\end{pmatrix}", r"}}")

latexmatrix = latexmatrix.replace(r"\\", r"},{")
latexmatrix = latexmatrix.replace(r"&", r",")

#optional
if (True):
    latexmatrix = latexmatrix.replace(r"x_3", r"x")
    latexmatrix = latexmatrix.replace(r"\lambda_1",r"y")
    latexmatrix = latexmatrix.replace(r"\lambda_2",r"z")
print(latexmatrix)
