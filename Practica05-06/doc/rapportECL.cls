\LoadClass[a4paper,12pt]{article} % Classe du document

%--------------------- Packages ------------------------

\RequirePackage[utf8]{inputenc} %Caractères spéciaux
\RequirePackage[section]{placeins}%Pour placement de section
\RequirePackage[T1]{fontenc} %Quelques lettres qui sont pas inclus dans UTF-8
\RequirePackage{mathtools} %Paquet pour des équations et symboles mathématiques
\RequirePackage{siunitx} %Pour écrire avec la notation scientifique (Ex.: \num{2e+9})
\RequirePackage{float} %Pour placement d'images
\RequirePackage{graphicx} %Paquet pour insérer des images
\RequirePackage[justification=centering]{caption} %Pour les légendes centralisées
\RequirePackage{subcaption}
\RequirePackage{wallpaper}
\RequirePackage{nomencl}
%\makenomenclature
\RequirePackage{fancyhdr}
%\pagestyle{fancy}
%\fancyheadoffset{1cm}
%\setlength{\headheight}{2cm}
\RequirePackage{url}
\RequirePackage[hidelinks]{hyperref}%Paquet pour insérer légendes dans des sous-figures comme Figure 1a, 1b
\RequirePackage[left=2.5cm,right=2.5cm,top=2cm,bottom=3.5cm]{geometry} %Configuration de la page


%-------------------- Informations sur le rapport ----------------------

\newcommand{\UE}[1]{\renewcommand{\UE}{#1}}
\newcommand{\sujet}[1]{\renewcommand{\sujet}{#1}}
\newcommand{\titre}[1]{\renewcommand{\titre}{#1}}
\newcommand{\enseignant}[1]{\renewcommand{\enseignant}{#1}}
\newcommand{\eleves}[1]{\renewcommand{\eleves}{#1}}

\newcommand{\fairemarges}{
\makenomenclature
\pagestyle{fancy}
\fancyheadoffset{1cm}
\setlength{\headheight}{2cm}
\lhead{\includegraphics[scale=0.25]{logos/csUNSA.png}}
\rhead{\nouppercase{\leftmark}}
\rfoot{\thepage}
\cfoot{}
\lfoot{\UE}
}

\newcommand{\fairepagedegarde}{
\begin{titlepage}
{\scshape\LARGE \textbf{“Año de la universalización de la salud”}.\par\vspace{1cm} }\\
\newline
\ThisLRCornerWallPaper{0.85}{logos/logoAguaUnsa.jpg}
	\centering %Centraliser le contenu
	\includegraphics[scale = 0.8]{logos/cs.png}\par\vspace{0.5cm} %Insertion du logo
	{\scshape\LARGE \textbf{Universidad Nacional de San Agust\'in de Arequipa\par}} %Nom de l'université
	\vspace{0.5cm}%Espace de 1,5cm
	{\scshape\Large \UE \\ \sujet \\ \par} %sous-titre
	\vspace{0.5cm}%Espace de 1cm
    \rule{\linewidth}{0.2 mm} \\[0.4 cm]
	{\huge\bfseries \titre \par} \
    \rule{\linewidth}{0.2 mm} \\[1cm]
	\vspace{0.5cm}%Espace de 3cm

	\begin{minipage}{0.8\textwidth} %Minipage pour faire deux colonnes
		\begin{flushleft} \large %Envoyer à gauche
		\emph{\textbf{Grupo 1A:}}\\ %Pour le titre au dessus des noms à gauche
        \eleves\\ %Remplacer pour chacun
		\end{flushleft}
		
		\begin{flushleft} \large %Envoyer à gauche
		\emph{\textbf{Docente:}}\\ %Pour le titre au dessus des noms à gauche
        \enseignant\\ %Remplacer pour chacun
		\end{flushleft}
	\end{minipage}
	
	%\begin{minipage}{0.4\textwidth}
	%	\begin{flushright} \large
	%	\emph{\textbf{Docente :}} \\
	%	 \enseignant \\
	%	\end{flushright}
	%\end{minipage}\\[2cm]

	\vfill
	{\large \today\par}%fecha

\end{titlepage}
}

%\newcommand{\Indice}{
%\tableofcontents
%\newpage
%}

\newcommand{\insererfigure}[4]{
\begin{figure}[ht]
\centering
\includegraphics[height=#2]{#1}
\caption{#3}
\label{fig: #4}
\end{figure}
}
