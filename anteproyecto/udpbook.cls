%
% Get the latest version and more at
% http://weblogs.udp.cl/carlos.fernandez/archivos/udptexmf.zip
%
% guide:      udpthesis.pdf
%
% template:   udpthesis.tex (for thesis)
%
% Carlos Fernandez, January 1, 2006.
% cfernandezj@gmail.com
%
% All names defined that includes an @ are internal
%
% ---------------------------------------------------------------------
% Bugs
%
% 2006/01/27 roman numeral for pages (fixed)
% spanish babel fake roman numeral with small caps
% work-around: redefine es@lsc 
% (true solution need some work)
%
% =====================================================================
% Identification
% ---------------------------------------------------------------------
                                           %
\NeedsTeXFormat{LaTeX2e}[1995/12/01]       % We need LaTeX2e or better
                                           %
\ProvidesClass{udpbook}[2006/01/27 v1.0 LaTeX2e UDP document class]
                                           %
% =====================================================================
% Preliminary declarations
% ---------------------------------------------------------------------
                                           %
\RequirePackage{udpbase}                   % base UDP package
                                           %
\RequirePackage{ifthen}                    % we need ifthenelse
% \newboolean are false by default         %
                                           %
% ---------------------------------------------------------------------
% Types of documents
% (no default. need explicit declaration)
                                           %
\newboolean{udp@bookthesis}                % thesis document
                                           %
% ---------------------------------------------------------------------
                                           %
\newboolean{udp@twoside}                   % twosides = false
\newboolean{udp@headers}                   % headers = false
                                           %
\newcommand{\udp@sides}{twoside}           % twoside is default
\setboolean{udp@twoside}{true}             %
                                           %
\newcommand{\udp@font}{computer modern}    % default for latex
\newboolean{udp@timesfont}                 % timesfont = false
                                           %
% ---------------------------------------------------------------------
% basic commands
                                           %
\newcommand{\udp@linespacing}              % inter line spacing
  {\onehalfspacing}                        %
                                           %
\newcommand{\udp@ptsize}{11pt}             % default font size
                                           %
\newcommand{\udp@indent}{30pt}             % indent (par., list,..)                                           %
                                           %
% define a new verion of LaTeX's raggedright to allow some hyphenation
% per Edward Tufte's book layout:
                                           %
\newcommand{\udp@raggedright}{             %
  \let\\\@centercr\@rightskip\z@ plus .5em % original = .1\hsize
  \rightskip\@rightskip\leftskip\z@skip    %
}                                          %
                                           %
%  first paragraph of chapter, section,...
                                           %
\newcommand{\fpar}{                        % no indented paragraph
  \par\noindent\ignorespaces               %
}                                          %
                                           %
% ---------------------------------------------------------------------
% define the spanish words for some titles %
                                           %
\newcommand{\udp@abstractname}             % abstract
  {Abstract}                               %
\newcommand{\udp@resumenname}              % abstract
  {Resumen}                                %
\newcommand{\@acknowledgmentname}          % acknowledgement
  {Agradecimientos}                        %
\newcommand{\udp@symbologyname}            % symbology
  {Simbolog\'{i}a y glosario}              %
\newcommand{\udp@dedicatoryname}           % dedicatory
  {Dedicatoria}                            %
\newcommand{\udp@refname}                  % references
  {Referencias}                            %
\newcommand{\udp@thesistext}               %
  {para optar al t\'{\i}tulo de}           %
                                           %
\newcommand{\udp@appendixtitle}            %
      {ANEXOS}                             %
\newcommand{\udp@draftmark}{               %
  {\bfseries BORRADOR \today}}             %
                                           %
% ---------------------------------------------------------------------
% define other fields                      %
                                           %
\newcommand{\@chairpersontitle}            %
  {Profesor gu\'{i}a}                      %
\newcommand{\udp@committeetext}            %
  {Comit\'{e}}                             %
                                           %
% ---------------------------------------------------------------------
% define commands for the title page       %
                                           %
%\newcommand{\degree}[1]{                   %
%  \gdef\udp@alumnidegree{#1}}              %
                                           %
\newcommand{\degreedoc}[3]{                %
  \gdef\udp@degreedoc{#1}                  %
  \gdef\udp@degreetitle{#2}                %
  \gdef\udp@alumnidegree{#3}}              %
                                           %
\newcommand{\chairperson}[1]{              %
  \gdef\@chairperson{#1}}                  %
                                           %
\newcommand{\committee}[1]{                %
  \gdef\udp@committeepersons{#1}}          %
                                           %
% ---------------------------------------------------------------------
% define spanish commands for the title page
                                           %
\newcommand{\grado}[1]{                    %
  \degree{#1}}                             %
\newcommand{\gradodoc}[1]{                 %
  \gradodoc{#1}}                           %
\newcommand{\profesorguia}[1]{             %
  \chairperson{#1}}                        %
\newcommand{\comite}[1]{                   %
  \committee{#1}}                          %
                                           %
% =====================================================================
% Options for the class
% ---------------------------------------------------------------------
                                           %
\DeclareOption{thesis}{                    % thesis document
  \setboolean{udp@bookthesis}{true}        %
  \setboolean{udp@headers}{false}          % have headers
}                                          %
                                           %
\DeclareOption{book}{                      % thesis document
  \setboolean{udp@bookthesis}{false}       %
  \setboolean{udp@headers}{true}           % have headers
}                                          %
                                           %
\DeclareOption{final}{                     % final
  \PassOptionsToClass{\CurrentOption}{book}%
  \renewcommand{\udp@draftmark}{}          % clear "draft"
}                                          %
                                           %
\DeclareOption{times}{                     % times font
  \renewcommand{\udp@font}{times}          %
  \setboolean{udp@timesfont}{true}         % use times font
}                                          %
                                           %
\DeclareOption{oneside}{                   % oneside
  \PassOptionsToClass{\CurrentOption}{book}%
  \setboolean{udp@twoside}{false}          %
  \renewcommand{\udp@sides}{oneside}       %
}                                          %
                                           %
\DeclareOption{twoside}{                   % twoside
  \PassOptionsToClass{\CurrentOption}{book}%
  \PassOptionsToClass{\CurrentOption}{geometry}
  \setboolean{udp@twoside}{true}           %
  \renewcommand{\udp@sides}{twoside}       %
}                                          %
                                           %
\DeclareOption{10pt}{                      % 10pt font size
  \renewcommand{\udp@ptsize}{10pt}         %
}                                          %
                                           %
\DeclareOption{11pt}{                      % 11pt font size
  \renewcommand{\udp@ptsize}{11pt}         %
}                                          %
                                           %
\DeclareOption{12pt}{                      % 12pt font size
  \renewcommand{\udp@ptsize}{12pt}         %
}                                          %
                                           %
\DeclareOption*{                           % unknown options
  \ClassError{udpbook}{                    %
    Unknown option [\CurrentOption].       %
  }{                                       %
    Delete option [\CurrentOption].        %
  }                                        %
}                                          %
                                           %
% =====================================================================
% Process options
% ---------------------------------------------------------------------
                                           %
\ProcessOptions\relax                      %
                                           %
% ---------------------------------------------------------------------
% Load other packages
% ---------------------------------------------------------------------
                                           %
\LoadClass[\udp@ptsize,\udp@sides]{book}   %
                                           %
\RequirePackage{geometry}                  %
\geometry{letterpaper}                     % letter paper
\ifthenelse{\boolean{udp@headers}}{        % check for headers
  \geometry{top=1.275in,bottom=1.275in}    % vertical borders
  \geometry{headheight=15pt}               % head height
}{                                         % no headers
  \geometry{top=0.900in,bottom=1.275in}    % vertical borders
  \geometry{nohead}                        % no headings
}                                          %
\geometry{left=1.750in,right=1.250in}      % horizontal borders
\geometry{marginparwidth=1.0in}            % margin notes width
\geometry{bindingoffset=0.50in}            % offset for bindings
                                           %
\RequirePackage[spanish]{babel}            % spanish language from babel
\RequirePackage{graphicx}                  %
\RequirePackage{epsfig}                    % for eps pictures
\RequirePackage{color}                     % color managment
\RequirePackage{calc}                      % provide calculations
\RequirePackage{setspace}                  % line spacing and ...
\RequirePackage{fancyhdr}                  % after package geometry
\RequirePackage{url}                       %
                                           %
\ifthenelse{\boolean{udp@timesfont}}{      % want to use times font?
  \RequirePackage{times}                   %
}{                                         %
}                                          %
                                           %
% =====================================================================
% More declarations
% ---------------------------------------------------------------------
                                           %
% redefine words for spanish babel
                                           %
\addto\captionsspanish{                    %
  \renewcommand{\contentsname}             % table of contents
    {Contenido}                            %
  \renewcommand{\listtablename}            % list of tables
    {Lista de tablas}                      %
  \renewcommand{\listfigurename}           % list of figures
    {Lista de figuras}                     %
  \renewcommand{\refname}                  %
    {Referencias bibliogr\'{a}ficas}       %
  \renewcommand{\bibname}                  %
    {Referencias bibliogr\'{a}ficas}       %
  \renewcommand{\indexname}                %
    {\'{I}ndice general}                   %
  \renewcommand{\tablename}                % name for tables
    {Tabla}                                %
  \renewcommand{\figurename}               % name for figures
    {Figura}                               %
  \renewcommand{\partname}                 %
    {Parte}                                %
  \renewcommand{\chaptername}              % chapter name
    {Cap\'{i}tulo}                         %
  \renewcommand{\appendixname}             % appendix name
    {Anexo}                                %
}                                          %
                                           %
% ---------------------------------------------------------------------
% 2006/01/27 bug fix
% spanish babel fake roman numeral with small caps
% need some work (this is not the best solution)
                                           %
\renewcommand{\es@lsc}[1]{                 % spanish babel
  #1                                       % strange things with roman
%  \typeout{----- es@lsc \showthe#1}        %
}                                          %
                                           %
% =====================================================================
% Actions for the whole document
% ---------------------------------------------------------------------
% some global actions
                                           %
\udp@linespacing                           % line spacing
                                           %
\setcounter{tocdepth}{2}                   % contents depth
\setcounter{secnumdepth}{2}                % section numbering depth
                                           %
\udp@raggedright                           %
                                           %
\setlength{\parindent}{\udp@indent}        % paragraph indent
                                           %
\fancyhf{}                                 % clear header/footer
                                           %
\pagestyle{fancy}                          % default style for pages
                                           %
% =====================================================================
% More declarations
% ---------------------------------------------------------------------
% headers and footers
                                           %
\renewcommand{\headrulewidth}{0.0pt}       %
\renewcommand{\footrulewidth}{0.0pt}       %
                                           %
\newcommand{\udp@frontmatterheaders}{      % headers for frontmatter
  \fancyhf{}                               %
  \ifthenelse{\boolean{udp@twoside}}{      %
    \fancyfoot[LE,RO]{\thepage}            %
    \fancyfoot[LO,RE]{\udp@draftmark}      %
  }{                                       %
    \fancyfoot[R]{\thepage}                %
    \fancyfoot[L]{\udp@draftmark}          %
  }                                        %
}                                          %
                                           %
\newcommand{\udp@mainmatterheaders}{       % headers for mainmatter
  \fancyhf{}                               %
  \ifthenelse{\boolean{udp@twoside}}{      %
    \ifthenelse{\boolean{udp@headers}}{    % two sides printing
      \fancyhead[RO]{\rightmark\ \         % with headers
        \thepage}                          %
      \fancyhead[LE]{\thepage              %
        \ \ \leftmark}                     %
      \fancyfoot[LO,RE]{\udp@draftmark}    %
    }{                                     %
      \fancyfoot[LE,RO]{\thepage}          % no headers
      \fancyfoot[LO,RE]{\udp@draftmark}    %
    }                                      %
  }{                                       %
    \fancyfoot[R]{\thepage}                % one side printing
    \fancyfoot[L]{\udp@draftmark}          %
  }                                        %
}                                          %
                                           %
\fancypagestyle{plain}{                    % redefine plain
  \fancyhead{}                             %
  \ifthenelse{\boolean{udp@twoside}}{      %
    \fancyfoot[L]{\udp@draftmark}          % two sides printing
    \fancyfoot[R]{\thepage}                %
  }{                                       %
    \fancyfoot[L]{\udp@draftmark}          % one side printing
    \fancyfoot[R]{\thepage}                %
  }                                        %
}                                          %
                                           %
% ---------------------------------------------------------------------
                                           %
\let\old@frontmatter=\frontmatter          % original frontmatter
                                           %
\renewcommand{\frontmatter}{               % redefine frontmatter
  \old@frontmatter                         %
  \udp@frontmatterheaders                  %
}                                          %
                                           %
\let\old@mainmatter=\mainmatter            % original mainmatter
                                           %
\renewcommand{\mainmatter}{                % redefine mainmatter
  \old@mainmatter                          %
  \udp@mainmatterheaders                   %
}                                          %
                                           %
% ---------------------------------------------------------------------
% redefine table of contents, figures and tables
% (not really needed but allows some extensions)
                                           %
\renewcommand{\tableofcontents}{           % tableofcontents command
  \chapter*{\contentsname}                 %
  \@starttoc{toc}                          %
}                                          %
                                           %
% ---------------------------------------------------------------------
                                           %
\renewcommand{\listoffigures}{             % listoffigures command
  \chapter*{\listfigurename}               %
  \@starttoc{lof}                          %
}                                          %
                                           %
% ---------------------------------------------------------------------
                                           %
\renewcommand{\listoftables}{              % listoftables command
  \chapter*{\listtablename}                %
  \@starttoc{lot}                          %
}                                          %
                                           %
% ---------------------------------------------------------------------
                                           %
\newcommand{\putbibliography}[1]{          % bibliography
  \cleardoublepage                         %
  \addcontentsline{toc}{chapter}           %
    {\bibname}                             %
  \bibliographystyle{udpbook}              % acm style
  \bibliography{#1}                        % biblio db file
}                                          %
                                           %
% ---------------------------------------------------------------------
                                           %
\renewcommand{\cleardoublepage}{           % double page eject
  \clearpage                               %
  \if@twoside                              %
    \ifodd\c@page\else                     %
      \hbox{}                              %
      \thispagestyle{empty}                %
      \newpage                             %
      \if@twocolumn\hbox{}                 %
        \newpage                           %
      \fi                                  %
    \fi                                    %
  \fi                                      %
}                                          %
                                           %
% ---------------------------------------------------------------------
% chapter and section marks
                                           %
\renewcommand{\chaptermark}[1]{            % chapter mark
  \markboth{                               %
%    \chaptername\ \thechapter\ #1          %
    #1                                   % chapter name
  }{}                                      %
}                                          %
                                           %
\renewcommand{\sectionmark}[1]{            % section mark
  \markright{                              %
%    \ifnum \c@secnumdepth >\z@             %
%      \thesection\                         %
%    \fi                                    %
    #1}                                    % section name
}                                          %
                                           %
% ---------------------------------------------------------------------
                                           %
                                           %
\renewcommand{\@makechapterhead}[1]{       % chapter head command
  \parindent \z@            % heading position
  \ifnum \c@secnumdepth >\m@ne             % check chapter numbering
    \if@mainmatter                         % Fix for mainmatter
      {                                    %
        \par\noindent\ignorespaces         %
        \Huge\bfseries                     %
        \@chapapp                          % chapter word (appendix bug)
%        \chaptername                       % chapter word (appendix bug)
        \space                             % space after chapter
        \thechapter\par\nobreak            % chapter number
      }                                    %
    \fi                                    %
  \fi                                      %
  \interlinepenalty\@M                     %
  \vskip 15em                              %
  {                                        %
    \par\noindent\ignorespaces             %
    \LARGE\bfseries                        %
    #1                                     % chapter name
  }                                        %
  \null\par                                %
  \noindent\ignorespaces                   %
  \rule[2pt]{\textwidth}{1pt}              % draw an horizontal line
  \vskip 4em                               % space after line
}                                          %
                                           %
\renewcommand\@makeschapterhead[1]{        % chapter* head command
  {                                        % (starred)
    \parindent \z@ \raggedright            %
    \interlinepenalty\@M                   %
    {                                      %
      \begin{center}                       %
        \LARGE\bfseries                    %
        #1                                 % chapter name
      \end{center}                         %
    }                                      %
    \par\nobreak                           %
    \vskip 2em                             %
  }                                        %
}                                          %
                                           %
\newcommand{\udp@labelchapter}             %
  {\chaptername\space\thechapter}          %
                                           %
\def\@chapter[#1]#2{                       %
  \refstepcounter{chapter}                 %
  \addcontentsline{toc}{chapter}           %
    {\protect%\numberline                  %
      {\udp@labelchapter\ \ #1}}           %
  \chaptermark{#1}                         %
  \@makechapterhead{#2}                    %
  \@afterheading                           %
}                                          %
                                           %
% ---------------------------------------------------------------------
% redefine appendix command
%
% generate a cover pages for appendices
% (must be equal to title page, except for the word \udp@appendixtitle)
                                           %
\renewcommand{\appendix}{                  % appendix
  \renewcommand{\@chapapp}{\appendixname}  %
  \renewcommand{\chaptername}{\appendixname} %
  \renewcommand{\thechapter}               %
    {\@Alph\c@chapter}                     %
  \setcounter{chapter}{0}                  %
  \setcounter{section}{0}                  %
  \cleardoublepage                         %
  \thispagestyle{empty}                    % generate a cover page
  \ifthenelse{\boolean{udp@bookthesis}}{   % thesis
    \begin{center}                         %
      \udp@logo{true}                      % put the logo picture
      \rule[2pt]{\textwidth}{2pt}          % draw an horizontal line
    \end{center}                           %
    \udp@coverpage{                        % appendix cover page
      \vskip 2em                           %
      \udp@appendixtitle                   % appendix title
      \vskip 10em                          %
      \@chairpersontitle                   % chairperson title
      \par                                 %
      \@chairperson                        % chairperson
      \vskip 2em                           %
      \udp@committeetext                   % committee label
      \par                                 %
      \udp@committeepersons                % committee
    }                                      %
    \newpage                               %
  }{                                       % book
  }                                        % haven't appendix cover page
}                                          %
                                           %
% ---------------------------------------------------------------------
%  environments for front matter           %
% ---------------------------------------------------------------------
                                           %
\newcommand{\udp@coverpage}[1]{            % cover page
  \vskip 1em                               %
  {\bfseries                               %
    \singlespacing                         %
    \begin{center}                         %
      {\LARGE\@title\par}                  % title
      \vskip 4em                           %
      {\large\@author}                     % author
      \vskip 6em                           %
      #1                                   %
      \vfill\null                          %
      \@date                               % date
    \end{center}                           %
  }                                        %
}                                          %
                                           %
% ---------------------------------------------------------------------
                                           %
\renewenvironment{titlepage}{              % titlepage
  \thispagestyle{empty}                    %
  \begin{center}                           %
    \udp@logo{true}                        % put the logo picture
    \rule[2pt]{\textwidth}{2pt}            % draw an horizontal line
  \end{center}                             %
}{                                         %
  \ifthenelse{\boolean{udp@bookthesis}}{   %
    \udp@coverpage{                        % thesis book
      \udp@degreedoc\                      % degree doc type
      para optar al \udp@degreetitle\ de   %
      \udp@alumnidegree                    % alumni degree
      \vskip 10em                          %
      \@chairpersontitle                   % chairperson title
      \par                                 %
      \@chairperson                        % chairperson
      \vskip 2em                           %
      \udp@committeetext                   %
      \par                                 %
      \udp@committeepersons                % committee
    }                                      %
  }{                                       %
    \udp@coverpage{                        % standard book
    }                                      %
  }                                        %
  \newpage                                 %
}                                          % end{titlepage}
                                           %
% ---------------------------------------------------------------------
                                           %
\newcommand{\copydate}[1]{                 % copyright date
  \gdef\udp@copydate{#1}}                  %
                                           %
\newenvironment{copyrights}{               % copyrights
  \newpage                                 %
  \thispagestyle{empty}                    %
  \begin{minipage}{.8\textwidth}           %
  \parindent=0pt                           %
  Esta publicación forma parte             %
  de las publicaciones de la               %
  \udp@Escuela, \udp@Facultad, \UDP.       %
  \vskip 2em                               %
  {\@author\par\@title}                    %
  \end{minipage}                           %
  \vskip 3em                               %
  \begin{minipage}{.8\textwidth}           %
}{                                         %
  \end{minipage}                           %
  \vfill                                   %
  \begin{minipage}{.8\textwidth}           %
  \parindent=0pt                           %
  Derechos reservados \copyright\          %
  \udp@copydate.                           %
  \par                                     %
  Todos los derechos reservados. Ninguna   %
  parte de esta publicación puede ser      %
  reproducida, almacenada o transmitida,   %
  de cualquier forma o por cualquier       %
  medio, ya sea electrónico, mecánico,     %
  fotocopiado, grabado o de otro modo,     %
  sin la previa aprobación de la \UDP.     %
  \end{minipage}                           %
  \newpage                                 % end page
  \setcounter{page}{1}                     % this is page i (one)
}                                          % end{copyrights}
                                           %
% ---------------------------------------------------------------------
% commands for the signature page
                                           %
\newcommand{\approval}[1]{                 % signature box
  \vskip 2.5em                             % space for sign
  \noindent                                %
  \begin{center}                           %
    {                                      %
      \bfseries                            %
      \parbox[t]{(\textwidth / 2) - 2em}{  % half of text width
        \begin{center}                     %
          \rule[2pt]{(\textwidth / 2) - 4em}{0.5pt} %
          \linebreak                       %
          \strut#1\strut                   %
        \end{center}                       %
      }                                    %
    }                                      %
  \end{center}                             %
}                                          %
                                           %
\newcommand{\approvaldouble}[2]{           % double signature box
  \vskip 2.5em                             % space for sign
  \noindent                                %
  \begin{center}                           %
    {                                      %
      \bfseries                            %
      \noindent\ignorespacesafterend       %
      \parbox[t]{(\textwidth / 2) - 2em}{  % half of text width
        \begin{center}                     %
          \rule[2pt]{(\textwidth / 2) - 4em}{0.5pt} %
          \linebreak                       %
          #1                               %
        \end{center}                       %
      }                                    %
      \hspace{2em}                         % space betwen two signs
      \parbox[t]{(\textwidth / 2) - 2em}{  %
        \begin{center}                     %
          \rule[0.2pt]{(\textwidth / 2) - 4em}{0.5pt} %
          \linebreak                       %
          #2                               %
        \end{center}                       %
      }                                    %
    }                                      %
  \end{center}                             %
}                                          %
                                           %
% ---------------------------------------------------------------------
                                           %
\newenvironment{signaturepage}{            % begin{signaturepage}
  \cleardoublepage                         %
  \thispagestyle{empty}                    %
  \singlespacing                           %
  \begin{center}                           %
    \udp@logo{false}                       %
    \rule[2pt]{\textwidth}{1pt}            % draw an horizontal line
  \end{center}                             %
  \vskip 1em                               %
  {\bfseries                               %
    \begin{center}                         %
      {\LARGE\@title\par}                  % title
      \vskip 2em                           %
      {\large\@author}                     % author
      \vskip 3em                           %
      \udp@degreedoc\                      % degree doc type
      para optar al \udp@degreetitle\ de   %
      \udp@alumnidegree                    % alumni degree
    \end{center}                           %
  }                                        %
  \vskip 4em                               % space before signatures
}{                                         %
  \vfill\null                              %
  {\bfseries                               %
    \begin{center}                         %
      \@date \par                          %
    \end{center}                           %
  }                                        %
  \newpage                                 % end page
  \setcounter{page}{1}                     % page 1 (frontmatter)
}                                          % end{signaturepage}
                                           %
% ---------------------------------------------------------------------
                                           %
\newenvironment{abstract}{                 % begin{abstract}
  \cleardoublepage                         %
  \chapter*{\udp@abstractname}             %
  \addcontentsline{toc}{chapter}           %
    {\udp@abstractname}                    %
}{                                         %
  \newpage                                 % end page
}                                          % end{abstract}
                                           %
% ---------------------------------------------------------------------
                                           %
\newenvironment{resumen}{                  % begin{resumen}
  \cleardoublepage                         %
  \chapter*{\udp@resumenname}              %
  \addcontentsline{toc}{chapter}           %
    {\udp@resumenname}                     %
}{                                         %
  \newpage                                 % end page
}                                          % end{resumen}
                                           %
% ---------------------------------------------------------------------
                                           %
\newenvironment{acknowledgment}{           % begin{acknowledgment}
  \cleardoublepage                         %
  \chapter*{\@acknowledgmentname}          %
}{                                         %
  \newpage                                 % end page
}                                          % end{acknowledgment}
                                           %
% ---------------------------------------------------------------------
                                           %
\newenvironment{dedicatory}{               % begin{dedicatory}
  \cleardoublepage                         %
  \thispagestyle{empty}                    %
  \hbox{}\vskip .61\textheight             %
  \slshape                                 % slanted
  \flushright                              % right justification
}{                                         %
  \newpage                                 % end page
}                                          % end{dedicatory}
                                           %
% ---------------------------------------------------------------------
                                           %
\newenvironment{symbology}{                % begin{symbology}
  \cleardoublepage                         %
  \chapter*{\udp@symbologyname}            %
  \addcontentsline{toc}{chapter}           %
    {\udp@symbologyname}                   %
  \begin{list}                             % symbols list
  {}                                       %
  {                                        %
    \setlength{\leftmargin}{\udp@indent}   %
    \setlength{\itemindent}{-\udp@indent}  %
    \setlength{\labelwidth}{0pt}           %
    \setlength{\itemsep}{0pt}              %
    \setlength{\parsep}{0pt}               %
    \setlength{\partopsep}{0pt}            %
    \setlength{\topsep}{0pt}               %
    \setlength{\labelsep}{1ex}             %
    \let\makelabel\descriptionlabel        % use description-list label
  }                                        %
}{                                         %
  \end{list}                               %
  \newpage                                 % end page
}                                          % end{symbology}
                                           %
% =====================================================================
% commands at begin and end of document
% ---------------------------------------------------------------------
                                           %
% Check some of the user directives and setup a few things
                                           %
%\AtBeginDocument{                          %
%}                                          %
                                           %
% ---------------------------------------------------------------------
                                           %
\AtEndDocument{                            %
  \if@openright                            % even number of pages
    \cleardoublepage                       %
  \else                                    %
    \clearpage                             %
  \fi                                      %
}                                          %
                                           %
\endinput
