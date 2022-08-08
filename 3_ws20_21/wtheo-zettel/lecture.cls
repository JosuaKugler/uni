\ProvidesClass{lecture}
\LoadClass[a4paper, titlepage]{article}

\RequirePackage[utf8]{inputenc}
\RequirePackage[T1]{fontenc}
\RequirePackage{textcomp}
\RequirePackage[german]{babel}
\RequirePackage{amsmath, amssymb, amsthm}
\RequirePackage{mdframed}
\RequirePackage{fancyhdr}
\RequirePackage{geometry}
\RequirePackage{import}
\RequirePackage{pdfpages}
\RequirePackage{transparent}
\RequirePackage{xcolor}
\RequirePackage{array}
\RequirePackage[shortlabels]{enumitem}
\RequirePackage{tikz}
\RequirePackage{pgfplots}
\RequirePackage[nobottomtitles]{titlesec}
\RequirePackage{listings}
\RequirePackage{mathtools}
\RequirePackage{forloop}
\RequirePackage{totcount}
\RequirePackage{calc}
\RequirePackage{wasysym}
\RequirePackage{environ}
\RequirePackage{bbm}
\RequirePackage{mathrsfs}

\usetikzlibrary{quotes, angles}
\pgfplotsset{
    compat=1.15,
    default 2d plot/.style={%
        grid=both,
        minor tick num=4,
        grid style={line width=.1pt, draw=gray!10},
        major grid style={line width=.2pt,draw=gray!50},
        axis lines=middle,
        enlargelimits={abs=0.2}
    },
}

\DeclareOption*{\PassOptionsToClass{\CurrentOption}{article}}
\DeclareOption{uebung}{
    \makeatletter
    \lhead{\@title}
    \rhead{\@author}
    \makeatother
}
\ProcessOptions\relax

% PAGE GEOMETRY
\geometry{
    left=15mm,
    right=40mm,
    top=20mm,
    bottom=20mm
}

% PARAGRAPH no indent but skip
\setlength{\parskip}{3mm}
\setlength{\parindent}{0mm}

\theoremstyle{definition}
\newmdtheoremenv{satz}{Satz}[section]
\newmdtheoremenv{lemma}[satz]{Lemma}
\newmdtheoremenv{korrolar}[satz]{Korrolar}
\newmdtheoremenv{definition}[satz]{Definition}

\newtheorem{bsp}[satz]{Beispiel}
\newtheorem{bem}[satz]{Bemerkung}
\newtheorem{aufgabe}{Aufgabe}

% enable aufgaben counting
\regtotcounter{aufgabe}

% temporary calculation counter
\newcounter{var}

\newcommand{\N}{\mathbb{N}}
\newcommand{\R}{\mathbb{R}}
\newcommand{\Z}{\mathbb{Z}}
\newcommand{\Q}{\mathbb{Q}}
\newcommand{\C}{\mathbb{C}}

% HEADERS

\pagestyle{fancy}

\newcommand{\incfig}[1]{%
    \def\svgwidth{\columnwidth}
    \import{./figures/}{#1.pdf_tex}
}
\pdfsuppresswarningpagegroup=1

% horizontal rule
\newcommand\hr{
    \noindent\rule[0.5ex]{\linewidth}{0.5pt}
}

% punkte tabelle
\newcommand{\punkte}[1][1]{
    \newcounter{k}
    \setcounter{k}{#1}
    \@punkten{\value{k}}{\totvalue{aufgabe}}
    \setcounter{k}{#1-1}
    \setcounter{aufgabe}{\value{k}}
    \vspace{5mm}
}

\def\@punkten#1#2{
    \newcounter{n}
    % create a temporary calculation counter
    \setcounter{var}{#2-#1+1}
    \begin{tabular}{|c|*{\value{var}}{m{1cm}|}m{1cm}|@{}m{0cm}@{}}
        \hline
        Aufgabe
        \forloop{n}{#1}{\not{\value{n} > #2}}{
            & \centering A\then
        }
        & \centering $\sum$ & \\[5mm] \hline
        Punkte
        \forloop{n}{#1}{\not{\value{n} > #2}}{
            &
        }
        & & \\[5mm] \hline
    \end{tabular}
}

% code listings, define style
\lstdefinestyle{mystyle}{
    commentstyle=\color{gray},
    keywordstyle=\color{blue},
    numberstyle=\tiny\color{gray},
    stringstyle=\color{black},
    basicstyle=\ttfamily\footnotesize,
    breakatwhitespace=false,         
    breaklines=true,                 
    captionpos=b,                    
    keepspaces=true,                 
    numbers=left,                    
    numbersep=5pt,                  
    showspaces=false,                
    showstringspaces=false,
    showtabs=false,                  
    tabsize=2
}

% activate my colour style
\lstset{style=mystyle}

% better stackrel
\let\oldstackrel\stackrel
\renewcommand{\stackrel}[2]{%
    \oldstackrel{\mathclap{#1}}{#2}
}%

% integral d sign
\makeatletter \renewcommand\d[2][]{\ensuremath{%
		\,\mathrm{d}^{#1}#2\@ifnextchar^{}{\@ifnextchar\d{}{\,}}}}
\makeatother

% contradiction
\newcommand{\contr}{\text{\Large\lightning}}

% disjoint unions: provides cupdot and bigcupdot
\makeatletter
\def\moverlay{\mathpalette\mov@rlay}
\def\mov@rlay#1#2{\leavevmode\vtop{%
   \baselineskip\z@skip \lineskiplimit-\maxdimen
   \ialign{\hfil$\m@th#1##$\hfil\cr#2\crcr}}}
\newcommand{\charfusion}[3][\mathord]{
    #1{\ifx#1\mathop\vphantom{#2}\fi
        \mathpalette\mov@rlay{#2\cr#3}
      }
    \ifx#1\mathop\expandafter\displaylimits\fi}
\makeatother

\newcommand{\cupdot}{\charfusion[\mathbin]{\cup}{\cdot}}
\newcommand{\bigcupdot}{\charfusion[\mathop]{\bigcup}{\cdot}}

\ExplSyntaxOn

% S-tackrelcompatible ALIGN environment
% some might also call it the S-uper ALIGN environment
% uses regular expressions to calculate the widest stackrel
% to put additional padding on both sides of relation symbols
\NewEnviron{salign}
{
    \begin{align}
        \lec_insert_padding:V \BODY
    \end{align}
}
% starred version that does no equation numbering
\NewEnviron{salign*}
{
    \begin{align*}
        \lec_insert_padding:V \BODY
    \end{align*}
}

% some helper variables
\tl_new:N \l__lec_text_tl
\seq_new:N \l_lec_stackrels_seq
\int_new:N \l_stackrel_count_int
\int_new:N \l_idx_int
\box_new:N \l_tmp_box
\dim_new:N \l_tmp_dim_a
\dim_new:N \l_tmp_dim_b
\dim_new:N \l_tmp_dim_needed

% function to insert padding according to widest stackrel
\cs_new_protected:Nn \lec_insert_padding:n
 {
  \tl_set:Nn \l__lec_text_tl { #1 }
  % get all stackrels in this align environment
  \regex_extract_all:nnN { \c{stackrel}{(.*?)}{(.*?)} } { #1 } \l_lec_stackrels_seq
  % get number of stackrels
  \int_set:Nn \l_stackrel_count_int { \seq_count:N \l_lec_stackrels_seq }
  \int_set:Nn \l_idx_int { 1 }
  \dim_set:Nn \l_tmp_dim_needed { 0pt }
  % iterate over stackrels
  \int_while_do:nn { \l_idx_int <= \l_stackrel_count_int }
  {
      % calculate width of text
      \hbox_set:Nn \l_tmp_box {$\seq_item:Nn \l_lec_stackrels_seq { \l_idx_int + 1 }$}
      \dim_set:Nn \l_tmp_dim_a {\box_wd:N \l_tmp_box}
      % calculate width of relation symbol
      \hbox_set:Nn \l_tmp_box {$\seq_item:Nn \l_lec_stackrels_seq { \l_idx_int + 2 }$}
      \dim_set:Nn \l_tmp_dim_b {\box_wd:N \l_tmp_box}
      % check if 0.5*(a-b) > minimum padding, if yes updated minimum padding
      \dim_compare:nNnTF
        { 1pt * \dim_ratio:nn { \l_tmp_dim_a - \l_tmp_dim_b } { 2pt } } > { \l_tmp_dim_needed }
        { \dim_set:Nn \l_tmp_dim_needed { 1pt * \dim_ratio:nn { \l_tmp_dim_a - \l_tmp_dim_b } { 2pt } } }
        { }
      \quad
      % increment list index by three, as every stackrel produces three list entries
      \int_incr:N \l_idx_int
      \int_incr:N \l_idx_int
      \int_incr:N \l_idx_int
  }
  % replace all relations with align characters (&) and add the needed padding
  \regex_replace_all:nnN
      { (\c{iff}&|&\c{iff}|\c{impliedby}&|&\c{impliedby}|\c{implies}&|&\c{implies}|\c{approx}&|&\c{approx}|\c{equiv}&|&\c{equiv}|=&|&=|\c{le}&|&\c{le}|\c{ge}&|&\c{ge}|&\c{stackrel}{.*?}{.*?}|\c{stackrel}{.*?}{.*?}&|&\c{neq}|\c{neq}&) }
      { \c{kern} \u{l_tmp_dim_needed} \1 \c{kern} \u{l_tmp_dim_needed} }
      \l__lec_text_tl
  \l__lec_text_tl
 }
\cs_generate_variant:Nn \lec_insert_padding:n { V }
\ExplSyntaxOff
