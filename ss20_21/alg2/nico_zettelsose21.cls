%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  class for zettel                                      %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%% identification							
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{nico_zettelsose21}[2021/04/18 Zettel class for SoSe2020]


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%% preliminary declarations
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\LoadClass[a4paper, titlepage, 11pt]{article}

\RequirePackage{mathhammer}






%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%% options
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%% Page Styles


\DeclareOption*{\PassOptionsToClass{\CurrentOption}{article}}

\ProcessOptions\relax




%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%% more declarations
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%




%\renewcommand{\normalsize}{\fontsize{9}{10}\selectfont}
%\setlength{\textwidth}{17.5cm}
%\setlength{\textheight}{22cm}
%\setcounter{secnumdepth}{0}





%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% new theorem styles
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\theoremstyle{definition}
\newtheorem{definition}{Definition}[section]
\newtheorem*{definition*}{Definition}
\newtheorem{satz}{Satz}[section]
\newtheorem*{satz*}{Satz}
\newtheorem*{beweis}{Beweis}
\newtheorem{korollar}{Korollar}[satz]
\newtheorem{bem}{Bemerkung}[section]
\newtheorem*{bem*}{Bemerkung}
\newtheorem{notationm}{Notation}[section]
\newtheorem{beisp}{Beispiel}[section]
\newtheorem*{beisp*}{Beispiel}
\newtheorem{prop}{Proposition}[section]
\newtheorem{lemma}{Lemma}[section]
\newtheorem*{lemma*}{Lemma}


\newtheoremstyle{aufgabe}% name of the style to be used
  {1pt}% measure of space to leave above the theorem. E.g.: 3pt
  {\topsep}% measure of space to leave below the theorem. E.g.: 3pt
  {}% name of font to use in the body of the theorem
  {0pt}% measure of space to indent
  {\bfseries}% name of head font
  { }% punctuation between head and body
  { }% space after theorem head; " " = normal interword space
  {\thmname{#1}\thmnumber{ #2}\thmnote{ (#3)}}
 
\theoremstyle{aufgabe}

\newtheorem*{zbeweis}{Beweis}



\newtheoremstyle{behauptungen}% name of the style to be used
  {0pt}% measure of space to leave above the theorem. E.g.: 3pt
  {\topsep}% measure of space to leave below the theorem. E.g.: 3pt
  {}% name of font to use in the body of the theorem
  {0pt}% measure of space to indent
  {\it}% name of head font
  {: }% punctuation between head and body
  { }% space after theorem head; " " = normal interword space
  {\thmname{#1}\thmnumber{ #2}\thmnote{ (#3)}}

\theoremstyle{behauptungen}
\newtheorem*{claim}{Claim}
\newtheorem*{prof}{Proof}
\newtheorem*{beh}{Behauptung}




\newcommand{\zzrm}{\textrm{\makebox[-.2mm][l]{z}\raisebox{0.5mm}{z}}}

\newcommand{\anaII}[1]{
\pagestyle{fancy}
\fancyhf{}
\rhead{Aufgabenblatt #1 \\ Ann Cathrin Wesener, Nico Haaf}
\lhead{Analysis 2 SoSe20 \\ Professor E. Kostina, Tutor: Peter Martin}
\rfoot{Seite \thepage}
\newtheorem*{zz}{Z.Z.}
}

\newcommand{\algII}[1]{
\pagestyle{fancy}
\fancyhf{}
\rhead{Josua Kugler, Nico Haaf}
\lhead{Algebra 2 SoSe21 Aufgabenblatt #1\\ Tutor: Arne Kuhrs}
\rfoot{Seite \thepage}
\newtheorem*{zz}{Z.Z.}
}

\newcommand{\funktheoIII}[1]{
\pagestyle{fancy}
\fancyhf{}
\rhead{Josua Kugler, Nico Haaf}
\lhead{Riemannsche Flächen SoSe 21 Aufgabenblatt #1}
\rfoot{Seite \thepage}
\newtheorem*{zz}{Z.Z.}
}

\newcommand{\numI}[1]{
\pagestyle{fancy}
\fancyhf{}
\rhead{Aufgabenblatt #1 \\ , Nico Haaf}
\lhead{Numerik 1 SoSe21 \\ Professor R. Scheichl, Tutor: Yara Elshiaty}
\rfoot{Seite \thepage}
\newtheorem*{zz}{Z.Z.}
}

