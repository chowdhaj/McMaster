

<!DOCTYPE html>

<html>
<head><meta charset="utf-8" /><meta name="viewport" content="width=device-width, initial-scale=1, minimum-scale=1, user-scalable=yes" /><meta http-equiv="X-UA-Compatible" content="IE=edge" />  <!-- For best MathJax performance on IE  -->

  <meta name="google-site-verification" content="uLoA31CJfOhIVMJWBjCmQL8xNMmmLybZU3LRKavy9WQ" /><title>
	Calculus II - Hydrostatic Pressure and Force
</title>

  <!-- Global site tag (gtag.js) - Google Analytics -->
  <script async src="https://www.googletagmanager.com/gtag/js?id=UA-331594-1"></script>
  <script>
    window.dataLayer = window.dataLayer || [];
    function gtag() { dataLayer.push(arguments); }
    gtag('js', new Date());

    gtag('config', 'UA-331594-1');
  </script>

  <link type="text/css" href="/css/jquery.mmenu.all.css" rel="stylesheet" /><link type="text/css" href="/css/jquery.dropdown.css" rel="stylesheet" /><link href="/FA/css/fontawesome-all.min.css" rel="stylesheet" /><link type="text/css" href="/css/notes-all.css" rel="stylesheet" /><link type="text/css" href="/css/notes-google.css" rel="stylesheet" /><link type="text/css" href="/css/notes-mmenu.css" rel="stylesheet" /><link type="text/css" href="/css/notes-dropdown.css" rel="stylesheet" />

  <script type="text/x-mathjax-config">
    MathJax.Hub.Config({
     TeX: { equationNumbers: { autoNumber: "AMS" } }
    });
  </script>
  <script type="text/javascript" async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.2/MathJax.js?config=TeX-AMS_CHTML-full"></script>
  <script type="text/javascript" src="https://code.jquery.com/jquery-3.4.0.min.js" integrity="sha256-BJeo0qm959uMBGb65z40ejJYGSgR7REI4+CW1fNKwOg=" crossorigin="anonymous"></script>
  <script type="text/javascript" src="/js/jquery.mmenu.all.js"></script>
  <script type="text/javascript" src="/js/jquery.dropdown.js"></script>
  <script type="text/javascript" src="/js/notes-all.js"></script>  

  <script>
    (function () {
      var cx = '001004262401526223570:11yv6vpcqvy';
      var gcse = document.createElement('script');
      gcse.type = 'text/javascript';
      gcse.async = true;
      gcse.src = 'https://cse.google.com/cse.js?cx=' + cx;
      var s = document.getElementsByTagName('script')[0];
      s.parentNode.insertBefore(gcse, s);
    })();
  </script>

<meta http-equiv="keywords" name="keywords" content="hydrostatic pressure, hydrostatic force, using integrals to find force" /><meta http-equiv="description" name="description" content="In this section we’ll determine the hydrostatic pressure and force on a vertical plate submerged in water.  The plates used in the examples can all be described as regions bounded by one or more curves/lines." /></head>
<body onload="init({Notes: 'NoteMobile;8/21/2018;true'})">

  <div id="page">

    <div class="header">
      <div class="header-row">
        <!--<a href="#menu"><span></span></a>-->
        <div id="side-menu-icon" class="header-side-menu-icon"><a href="#menu"><span class="fas fa-bars fa-lg" aria-hidden="true" title="Main Menu - Change between topics, chapters and sections as well as a few extra pages."></span></a></div>
        <span class="header-title"><a href="/" class="header-title-link">Paul's Online Notes</a></span>
        <div class="header-spacer"></div>

        <div id="content-top-menu" class="top-menu">
          <button id="content-type-menu" class="top-menu-button" data-jq-dropdown="#jq-dropdown-type" title="View (Notes, Practice Problems or Assignment Problems, Show/Hide Solutions and/or Steps) Menu">
            <span id="tab_top_menu_notes" class="top-menu-item-title">Notes</span> <span class="far fa-eye fa-lg" aria-hidden="true"></span>
          </button>

          <button id="quicknav-menu" class="top-menu-button" data-jq-dropdown="#jq-dropdown-quicknav" title="Quick Navigation (Previous/Next Sections and Problems and Full Problem List) Menu">
            <span class="top-menu-item-title">Quick Nav</span> <span class="fas fa-exchange fa-lg" aria-hidden="true"></span>
          </button>
          
          <button id="download-menu" class="top-menu-button" data-jq-dropdown="#jq-dropdown-download" title="Download pdf Menu">
            <span class="top-menu-item-title">Download</span> <span class="far fa-download fa-lg" aria-hidden="true"></span>
          </button>

          <button id="print-menu" class="top-menu-button top-menu-button-icon-only" data-jq-dropdown="#jq-print-download" title="Print Menu">
            <span class="far fa-print fa-lg" aria-hidden="true"></span>
          </button>
        </div>

        <div id="header-google-search" class="header-search">
          <gcse:search></gcse:search>
        </div>
        <div id="header-search-icon" title="Site Search" class="header-menu-icon"><span id="search-icon" class="fas fa-search" aria-hidden="true"></span></div>

      </div>
    </div>

     <div id="jq-dropdown-type" class="jq-dropdown jq-dropdown-tip">
      <ul class="jq-dropdown-menu">
        
        <li id="li_type_menu_goto" class="top-menu-nav-title">Go To</li>
        <li id="li_type_menu_notes">
          <span id="type_menu_notes_span" title="Viewing the Notes for the current topic." class="top-menu-current">Notes</span>
          
        </li>
        <li id="li_type_menu_practice">
          
          
          <a href="/Problems/CalcII/HydrostaticPressure.aspx" id="type_menu_practice_link" title="Go to Practice Problems for current topic.">Practice Problems</a>
        </li>
        <li id="li_type_menu_asgn">
          
          <a href="/ProblemsNS/CalcII/HydrostaticPressure.aspx" id="type_menu_asgn_link" title="Go to Assignment Problems for current topic.">Assignment Problems</a>
        </li>
        <li id="li_type_menu_sh" class="top-menu-nav-title">Show/Hide</li>
        <li id="li_type_menu_show" title="Show any hidden solutions and/or steps that may be present on the page."><a href="javascript:SHPrintPage(1,0)" id="view_menu_show">Show all Solutions/Steps/<em>etc.</em></a></li>
        <li id="li_type_menu_hide" title="Hide any visible solutions and/or steps that may be present on the page."><a href="javascript:SHPrintPage(0,0)" id="view_menu_hide">Hide all Solutions/Steps/<em>etc.</em></a></li>
      </ul>
    </div>

    <div id="jq-dropdown-quicknav" class="jq-dropdown jq-dropdown-tip">
      <ul class="jq-dropdown-menu">
        <li id="li_nav_menu_sections" class="top-menu-nav-title">Sections</li>
        <li id="li_nav_menu_prev_section"><a href="/Classes/CalcII/CenterOfMass.aspx" id="a_nav_menu_prev_section" class="top-menu-nav-link" title="Previous Section : Center of Mass"><span class="top-menu-prev fas fa-chevron-left"></span> Center of Mass</a></li>
        <li id="li_nav_menu_next_section"><a href="/Classes/CalcII/Probability.aspx" id="a_nav_menu_next_section" class="top-menu-nav-link" title="Next Section : Probability"><span class="top-menu-prev-hidden fas fa-chevron-left"></span> Probability <span class="top-menu-next fas fa-chevron-right"></span></a></li>
        <li id="li_nav_menu_chapters" class="top-menu-nav-title">Chapters</li>
        <li id="li_nav_menu_prev_chapter"><a href="/Classes/CalcII/IntTechIntro.aspx" id="a_nav_menu_prev_chapter" class="top-menu-nav-link" title="Previous Chapter : Integration Techniques"><span class="top-menu-prev fas fa-chevron-left"></span><span class="top-menu-prev fas fa-chevron-left"></span> Integration Techniques</a></li>
        <li id="li_nav_menu_next_chapter"><a href="/Classes/CalcII/ParametricIntro.aspx" id="a_nav_menu_next_chapter" class="top-menu-nav-link" title="Next Chapter : Parametric Equations and Polar Coordinates"><span class="top-menu-prev-hidden fas fa-chevron-left"></span><span class="top-menu-prev-hidden fas fa-chevron-left"></span> Parametric Equations and Polar Coordinates <span class="top-menu-next fas fa-chevron-right"></span><span class="top-menu-next fas fa-chevron-right"></span></a></li>
        
        
        
        
        <li id="li_nav_menu_classes" class="top-menu-nav-title">Classes</li>
        <li>
          
          <a href="/Classes/Alg/Alg.aspx" id="nav_menu_alg_link" title="Go To Algebra Notes">Algebra</a>
        </li>
        <li>
          
          <a href="/Classes/CalcI/CalcI.aspx" id="nav_menu_calci_link" title="Go To Calculus I Notes">Calculus I</a>
        </li>
        <li>
          <span id="nav_menu_calcii_span" title="Currently Viewing Calculus II Material" class="top-menu-current">Calculus II</span>
          
        </li>
        <li>
          
          <a href="/Classes/CalcIII/CalcIII.aspx" id="nav_menu_calciii_link" title="Go To Calculus III Notes">Calculus III</a>
        </li>
        <li>
          
          <a href="/Classes/DE/DE.aspx" id="nav_menu_de_link" title="Go To Differential Equations Notes">Differential Equations</a>
        </li>
        <li id="li_nav_menu_extras" class="top-menu-nav-title">Extras</li>
        <li>
          
          <a href="/Extras/AlgebraTrigReview/AlgebraTrig.aspx" id="nav_menu_algtrig_link" title="Go To Algebra &amp; Trig Review">Algebra &amp; Trig Review</a>
        </li>
        <li>
          
          <a href="/Extras/CommonErrors/CommonMathErrors.aspx" id="nav_menu_commonerrors_link" title="Go To Common Math Errors">Common Math Errors</a>
        </li>
        <li>
          
          <a href="/Extras/ComplexPrimer/ComplexNumbers.aspx" id="nav_menu_complexnumbers_link" title="Go To Complex Numbers Primer">Complex Number Primer</a>
        </li>
        <li>
          
          <a href="/Extras/StudyMath/HowToStudyMath.aspx" id="nav_menu_studymath_link" title="Go To How To Study Math">How To Study Math</a>
        </li>
        <li>
          
          <a href="/Extras/CheatSheets_Tables.aspx" id="nav_menu_cheattables_link" title="Go To List of Cheat Sheets and Tables">Cheat Sheets &amp; Tables</a>
        </li>
        <li id="li_nav_menu_misc" class="top-menu-nav-title">Misc</li>
        <li><a href="/contact.aspx" id="nav_menu_contact" title="Contact Me!">Contact Me</a></li>
        <li><a href="/mathjax.aspx" id="nav_menu_mathjax" title="Info on MathJax and MathJax Configuration Menu">MathJax Help and Configuration</a></li>
        <li><a href="/mystudents.aspx" id="nav_menu_students" title="Go here if you are currently taking a class from me!">My Students</a></li>
      </ul>
    </div>

    <div id="jq-dropdown-download" class="jq-dropdown jq-dropdown-anchor-right jq-dropdown-tip">
      <ul class="jq-dropdown-menu">
        
        <li id="li_download_menu_notes" class="top-menu-nav-title">Notes Downloads</li>
        <li id="li_download_menu_notes_book"><a href="/GetFile.aspx?file=B,2,N" id="download_menu_notes_book" data-PDF="Download - Menu$Notes - Book$Calculus II$/Downloads/CalcII/Notes/Complete.pdf">Complete Book</a></li>
        
        <li id="li_download_menu_notes_chapter"><a href="/GetFile.aspx?file=C,7,N" id="download_menu_notes_chapter" data-PDF="Download - Menu$Notes - Chapter$Calculus II - Applications of Integrals$/Downloads/CalcII/Notes/IntegralApps.pdf">Current Chapter</a></li>
        <li id="li_download_menu_notes_section"><a href="/GetFile.aspx?file=S,288,N" id="download_menu_notes_section" data-PDF="Download - Menu$Notes - Section$Calculus II - Hydrostatic Pressure and Force$/Downloads/CalcII/Notes/HydrostaticPressure.pdf">Current Section</a></li>
        <li id="li_download_menu_practice" class="top-menu-nav-title">Practice Problems Downloads</li>
        
        <li id="li_download_menu_practice_book"><a href="/GetFile.aspx?file=B,2,P" id="download_menu_practice_book" data-PDF="Download - Menu$Practice Problems - Book$Calculus II$/Downloads/CalcII/Practice Problems/Complete.pdf">Complete Book - Problems Only</a></li>
        <li id="li_download_menu_solutions_book"><a href="/GetFile.aspx?file=B,2,S" id="download_menu_solutions_book" data-PDF="Download - Menu$Practice Problems Solutions - Book$Calculus II$/Downloads/CalcII/Practice Problems Solutions/Complete.pdf">Complete Book - Solutions</a></li>
        <li id="li_download_menu_b_c" class="top-menu-divider"></li>
        <li id="li_download_menu_practice_chapter"><a href="/GetFile.aspx?file=C,7,P" id="download_menu_practice_chapter" data-PDF="Download - Menu$Practice Problems - Chapter$Calculus II - Applications of Integrals$/Downloads/CalcII/Practice Problems/IntegralApps.pdf">Current Chapter - Problems Only</a></li>
        <li id="li_download_menu_solutions_chapter"><a href="/GetFile.aspx?file=C,7,S" id="download_menu_solutions_chapter" data-PDF="Download - Menu$Practice Problems Solutions - Chapter$Calculus II - Applications of Integrals$/Downloads/CalcII/Practice Problems Solutions/IntegralApps.pdf">Current Chapter - Solutions</a></li>
        <li id="li_download_menu_c_s" class="top-menu-divider"></li>
        <li id="li_download_menu_practice_section"><a href="/GetFile.aspx?file=S,288,P" id="download_menu_practice_section" data-PDF="Download - Menu$Practice Problems - Section$Calculus II - Hydrostatic Pressure and Force$/Downloads/CalcII/Practice Problems/HydrostaticPressure.pdf">Current Section - Problems Only</a></li>
        <li id="li_download_menu_solutions_section"><a href="/GetFile.aspx?file=S,288,S" id="download_menu_solutions_section" data-PDF="Download - Menu$Practice Problems Solutions - Section$Calculus II - Hydrostatic Pressure and Force$/Downloads/CalcII/Practice Problems Solutions/HydrostaticPressure.pdf">Current Section - Solutions</a></li>
        <li id="li_download_menu_asgn" class="top-menu-nav-title">Assignment Problems Downloads</li>
        
        <li id="li_download_menu_asgn_book"><a href="/GetFile.aspx?file=B,2,A" id="download_menu_asgn_book" data-PDF="Download - Menu$Assignment Problems - Book$Calculus II$/Downloads/CalcII/Assignment Problems/Complete.pdf">Complete Book</a></li>
        <li id="li_download_menu_asgn_chapter"><a href="/GetFile.aspx?file=C,7,A" id="download_menu_asgn_chapter" data-PDF="Download - Menu$Assignment Problems - Chapter$Calculus II - Applications of Integrals$/Downloads/CalcII/Assignment Problems/IntegralApps.pdf">Current Chapter</a></li>
        <li id="li_download_menu_asgn_section"><a href="/GetFile.aspx?file=S,288,A" id="download_menu_asgn_section" data-PDF="Download - Menu$Assignment Problems - Section$Calculus II - Hydrostatic Pressure and Force$/Downloads/CalcII/Assignment Problems/HydrostaticPressure.pdf">Current Section</a></li>
        <li id="li_download_menu_other" class="top-menu-nav-title">Other Items</li>
        <li id="li_download_menu_urls">
          <a href="/DownloadURLs.aspx?bi=2&ci=7&si=288" id="download_menu_urls">Get URL's for Download Items</a>
        </li>
      </ul>
    </div>

    <div id="jq-print-download" class="jq-dropdown jq-dropdown-anchor-right jq-dropdown-tip">
      <ul class="jq-dropdown-menu">
        <li id="li_print_menu_default"><a href="javascript:SHPrintPage()" id="print_menu_default">Print Page in Current Form (Default)</a></li>
        <li id="li_print_menu_show"><a href="javascript:SHPrintPage(1,1)" id="print_menu_show">Show all Solutions/Steps and Print Page</a></li>
        <li id="li_print_menu_hide"><a href="javascript:SHPrintPage(0,1)" id="print_menu_hide">Hide all Solutions/Steps and Print Page</a></li>
      </ul>
    </div>



   

    <nav id="menu" class="notes-nav">
      <ul>
        <li><a href="/" class="mm-link">Home</a></li>
        <li><span>Classes</span></li>
        <li><a href="/Classes/Alg/Alg.aspx" class="mm-link">Algebra</a>
          <ul>
            <li><a href="/Classes/Alg/Preliminaries.aspx" class="mm-link">Preliminaries</a>
              <ul>
                <li><a href="/Classes/Alg/IntegerExponents.aspx" class="mm-link">Integer Exponents</a></li>
                <li><a href="/Classes/Alg/RationalExponents.aspx" class="mm-link">Rational Exponents</a></li>
                <li><a href="/Classes/Alg/Radicals.aspx" class="mm-link">Radicals</a></li>
                <li><a href="/Classes/Alg/Polynomials.aspx" class="mm-link">Polynomials</a></li>
                <li><a href="/Classes/Alg/Factoring.aspx" class="mm-link">Factoring Polynomials</a></li>
                <li><a href="/Classes/Alg/RationalExpressions.aspx" class="mm-link">Rational Expressions</a></li>
                <li><a href="/Classes/Alg/ComplexNumbers.aspx" class="mm-link">Complex Numbers</a></li>
              </ul>
            </li>
            <li><a href="/Classes/Alg/Solving.aspx" class="mm-link">Solving Equations and Inequalities</a>
              <ul>
                <li><a href="/Classes/Alg/SolutionSets.aspx" class="mm-link">Solutions and Solution Sets</a></li>
                <li><a href="/Classes/Alg/SolveLinearEqns.aspx" class="mm-link">Linear Equations</a></li>
                <li><a href="/Classes/Alg/LinearApps.aspx" class="mm-link">Applications of Linear Equations</a></li>
                <li><a href="/Classes/Alg/SolveMultiVariable.aspx" class="mm-link">Equations With More Than One Variable</a></li>
                <li><a href="/Classes/Alg/SolveQuadraticEqnsI.aspx" class="mm-link">Quadratic Equations - Part I</a></li>
                <li><a href="/Classes/Alg/SolveQuadraticEqnsII.aspx" class="mm-link">Quadratic Equations - Part II</a></li>
                <li><a href="/Classes/Alg/SolveQuadraticEqnSummary.aspx" class="mm-link">Quadratic Equations : A Summary</a></li>
                <li><a href="/Classes/Alg/QuadraticApps.aspx" class="mm-link">Applications of Quadratic Equations</a></li>
                <li><a href="/Classes/Alg/ReducibleToQuadratic.aspx" class="mm-link">Equations Reducible to Quadratic in Form</a></li>
                <li><a href="/Classes/Alg/SolveRadicalEqns.aspx" class="mm-link">Equations with Radicals</a></li>
                <li><a href="/Classes/Alg/SolveLinearInequalities.aspx" class="mm-link">Linear Inequalities</a></li>
                <li><a href="/Classes/Alg/SolvePolyInequalities.aspx" class="mm-link">Polynomial Inequalities</a></li>
                <li><a href="/Classes/Alg/SolveRationalInequalities.aspx" class="mm-link">Rational Inequalities</a></li>
                <li><a href="/Classes/Alg/SolveAbsValueEqns.aspx" class="mm-link">Absolute Value Equations</a></li>
                <li><a href="/Classes/Alg/SolveAbsValueIneq.aspx" class="mm-link">Absolute Value Inequalities</a></li>
              </ul>
            </li>
            <li><a href="/Classes/Alg/Graphing_Functions.aspx" class="mm-link">Graphing and Functions</a>
              <ul>
                <li><a href="/Classes/Alg/Graphing.aspx" class="mm-link">Graphing</a></li>
                <li><a href="/Classes/Alg/Lines.aspx" class="mm-link">Lines</a></li>
                <li><a href="/Classes/Alg/Circles.aspx" class="mm-link">Circles</a></li>
                <li><a href="/Classes/Alg/FunctionDefn.aspx" class="mm-link">The Definition of a Function</a></li>
                <li><a href="/Classes/Alg/GraphFunctions.aspx" class="mm-link">Graphing Functions</a></li>
                <li><a href="/Classes/Alg/CombineFunctions.aspx" class="mm-link">Combining Functions</a></li>
                <li><a href="/Classes/Alg/InverseFunctions.aspx" class="mm-link">Inverse Functions</a></li>
              </ul>
            </li>
            <li><a href="/Classes/Alg/CommonGraphs.aspx" class="mm-link">Common Graphs</a>
              <ul>
                <li><a href="/Classes/Alg/Lines_Circles_PWF.aspx" class="mm-link">Lines, Circles and Piecewise Functions</a></li>
                <li><a href="/Classes/Alg/Parabolas.aspx" class="mm-link">Parabolas</a></li>
                <li><a href="/Classes/Alg/Ellipses.aspx" class="mm-link">Ellipses</a></li>
                <li><a href="/Classes/Alg/Hyperbolas.aspx" class="mm-link">Hyperbolas</a></li>
                <li><a href="/Classes/Alg/MiscFunctions.aspx" class="mm-link">Miscellaneous Functions</a></li>
                <li><a href="/Classes/Alg/Transformations.aspx" class="mm-link">Transformations</a></li>
                <li><a href="/Classes/Alg/Symmetry.aspx" class="mm-link">Symmetry</a></li>
                <li><a href="/Classes/Alg/GraphRationalFcns.aspx" class="mm-link">Rational Functions</a></li>
              </ul>
            </li>
            <li><a href="/Classes/Alg/PolynomialFunctions.aspx" class="mm-link">Polynomial Functions</a>
              <ul>
                <li><a href="/Classes/Alg/DividingPolynomials.aspx" class="mm-link">Dividing Polynomials</a></li>
                <li><a href="/Classes/Alg/ZeroesOfPolynomials.aspx" class="mm-link">Zeroes/Roots of Polynomials</a></li>
                <li><a href="/Classes/Alg/GraphingPolynomials.aspx" class="mm-link">Graphing Polynomials</a></li>
                <li><a href="/Classes/Alg/FindingZeroesOfPolynomials.aspx" class="mm-link">Finding Zeroes of Polynomials</a></li>
                <li><a href="/Classes/Alg/PartialFractions.aspx" class="mm-link">Partial Fractions</a></li>
              </ul>
            </li>
            <li><a href="/Classes/Alg/ExpAndLog.aspx" class="mm-link">Exponential and Logarithm Functions</a>
              <ul>
                <li><a href="/Classes/Alg/ExpFunctions.aspx" class="mm-link">Exponential Functions</a></li>
                <li><a href="/Classes/Alg/LogFunctions.aspx" class="mm-link">Logarithm Functions</a></li>
                <li><a href="/Classes/Alg/SolveExpEqns.aspx" class="mm-link">Solving Exponential Equations</a></li>
                <li><a href="/Classes/Alg/SolveLogEqns.aspx" class="mm-link">Solving Logarithm Equations</a></li>
                <li><a href="/Classes/Alg/ExpLogApplications.aspx" class="mm-link">Applications</a></li>
              </ul>
            </li>
            <li><a href="/Classes/Alg/Systems.aspx" class="mm-link">Systems of Equations</a>
              <ul>
                <li><a href="/Classes/Alg/SystemsTwoVrble.aspx" class="mm-link">Linear Systems with Two Variables</a></li>
                <li><a href="/Classes/Alg/SystemsThreeVrble.aspx" class="mm-link">Linear Systems with Three Variables</a></li>
                <li><a href="/Classes/Alg/AugmentedMatrix.aspx" class="mm-link">Augmented Matrices</a></li>
                <li><a href="/Classes/Alg/AugmentedMatrixII.aspx" class="mm-link">More on the Augmented Matrix</a></li>
                <li><a href="/Classes/Alg/NonlinearSystems.aspx" class="mm-link">Nonlinear Systems</a></li>
              </ul>
            </li>
          </ul>
        </li>

        <li><a href="/Classes/CalcI/CalcI.aspx" class="mm-link">Calculus I</a>
          <ul>
            <li><a href="/Classes/CalcI/ReviewIntro.aspx" class="mm-link">Review</a>
              <ul>
                <li><a href="/Classes/CalcI/Functions.aspx" class="mm-link">Functions</a></li>
                <li><a href="/Classes/CalcI/InverseFunctions.aspx" class="mm-link">Inverse Functions</a></li>
                <li><a href="/Classes/CalcI/TrigFcns.aspx" class="mm-link">Trig Functions</a></li>
                <li><a href="/Classes/CalcI/TrigEquations.aspx" class="mm-link">Solving Trig Equations</a></li>
                <li><a href="/Classes/CalcI/TrigEquations_CalcI.aspx" class="mm-link">Trig Equations with Calculators, Part I</a></li>
                <li><a href="/Classes/CalcI/TrigEquations_CalcII.aspx" class="mm-link">Trig Equations with Calculators, Part II</a></li>
                <li><a href="/Classes/CalcI/ExpFunctions.aspx" class="mm-link">Exponential Functions</a></li>
                <li><a href="/Classes/CalcI/LogFcns.aspx" class="mm-link">Logarithm Functions</a></li>
                <li><a href="/Classes/CalcI/ExpLogEqns.aspx" class="mm-link">Exponential and Logarithm Equations</a></li>
                <li><a href="/Classes/CalcI/CommonGraphs.aspx" class="mm-link">Common Graphs</a></li>
              </ul>
            </li>
            <li><a href="/Classes/CalcI/limitsIntro.aspx" class="mm-link">Limits</a>
              <ul>
                <li><a href="/Classes/CalcI/Tangents_Rates.aspx" class="mm-link">Tangent Lines and Rates of Change</a></li>
                <li><a href="/Classes/CalcI/TheLimit.aspx" class="mm-link">The Limit</a></li>
                <li><a href="/Classes/CalcI/OneSidedLimits.aspx" class="mm-link">One-Sided Limits</a></li>
                <li><a href="/Classes/CalcI/LimitsProperties.aspx" class="mm-link">Limit Properties</a></li>
                <li><a href="/Classes/CalcI/ComputingLimits.aspx" class="mm-link">Computing Limits</a></li>
                <li><a href="/Classes/CalcI/InfiniteLimits.aspx" class="mm-link">Infinite Limits</a></li>
                <li><a href="/Classes/CalcI/LimitsAtInfinityI.aspx" class="mm-link">Limits At Infinity, Part I</a></li>
                <li><a href="/Classes/CalcI/LimitsAtInfinityII.aspx" class="mm-link">Limits At Infinity, Part II</a></li>
                <li><a href="/Classes/CalcI/Continuity.aspx" class="mm-link">Continuity</a></li>
                <li><a href="/Classes/CalcI/DefnOfLimit.aspx" class="mm-link">The Definition of the Limit</a></li>
              </ul>
            </li>
            <li><a href="/Classes/CalcI/DerivativeIntro.aspx" class="mm-link">Derivatives</a>
              <ul>
                <li><a href="/Classes/CalcI/DefnOfDerivative.aspx" class="mm-link">The Definition of the Derivative</a></li>
                <li><a href="/Classes/CalcI/DerivativeInterp.aspx" class="mm-link">Interpretation of the Derivative</a></li>
                <li><a href="/Classes/CalcI/DiffFormulas.aspx" class="mm-link">Differentiation Formulas</a></li>
                <li><a href="/Classes/CalcI/ProductQuotientRule.aspx" class="mm-link">Product and Quotient Rule</a></li>
                <li><a href="/Classes/CalcI/DiffTrigFcns.aspx" class="mm-link">Derivatives of Trig Functions</a></li>
                <li><a href="/Classes/CalcI/DiffExpLogFcns.aspx" class="mm-link">Derivatives of Exponential and Logarithm Functions</a></li>
                <li><a href="/Classes/CalcI/DiffInvTrigFcns.aspx" class="mm-link">Derivatives of Inverse Trig Functions</a></li>
                <li><a href="/Classes/CalcI/DiffHyperFcns.aspx" class="mm-link">Derivatives of Hyperbolic Functions</a></li>
                <li><a href="/Classes/CalcI/ChainRule.aspx" class="mm-link">Chain Rule</a></li>
                <li><a href="/Classes/CalcI/ImplicitDIff.aspx" class="mm-link">Implicit Differentiation</a></li>
                <li><a href="/Classes/CalcI/RelatedRates.aspx" class="mm-link">Related Rates</a></li>
                <li><a href="/Classes/CalcI/HigherOrderDerivatives.aspx" class="mm-link">Higher Order Derivatives</a></li>
                <li><a href="/Classes/CalcI/LogDiff.aspx" class="mm-link">Logarithmic Differentiation</a></li>
              </ul>
            </li>
            <li><a href="/Classes/CalcI/DerivAppsIntro.aspx" class="mm-link">Applications of Derivatives</a>
              <ul>
                <li><a href="/Classes/CalcI/RateOfChange.aspx" class="mm-link">Rates of Change</a></li>
                <li><a href="/Classes/CalcI/CriticalPoints.aspx" class="mm-link">Critical Points</a></li>
                <li><a href="/Classes/CalcI/MinMaxValues.aspx" class="mm-link">Minimum and Maximum Values</a></li>
                <li><a href="/Classes/CalcI/AbsExtrema.aspx" class="mm-link">Finding Absolute Extrema</a></li>
                <li><a href="/Classes/CalcI/ShapeofGraphPtI.aspx" class="mm-link">The Shape of a Graph, Part I</a></li>
                <li><a href="/Classes/CalcI/ShapeofGraphPtII.aspx" class="mm-link">The Shape of a Graph, Part II</a></li>
                <li><a href="/Classes/CalcI/MeanValueTheorem.aspx" class="mm-link">The Mean Value Theorem</a></li>
                <li><a href="/Classes/CalcI/Optimization.aspx" class="mm-link">Optimization</a></li>
                <li><a href="/Classes/CalcI/MoreOptimization.aspx" class="mm-link">More Optimization Problems</a></li>
                <li><a href="/Classes/CalcI/LHospitalsRule.aspx" class="mm-link">L'Hospital's Rule and Indeterminate Forms</a></li>
                <li><a href="/Classes/CalcI/LinearApproximations.aspx" class="mm-link">Linear Approximations</a></li>
                <li><a href="/Classes/CalcI/Differentials.aspx" class="mm-link">Differentials</a></li>
                <li><a href="/Classes/CalcI/NewtonsMethod.aspx" class="mm-link">Newton's Method</a></li>
                <li><a href="/Classes/CalcI/BusinessApps.aspx" class="mm-link">Business Applications</a></li>
              </ul>
            </li>
            <li><a href="/Classes/CalcI/IntegralsIntro.aspx" class="mm-link">Integrals</a>
              <ul>
                <li><a href="/Classes/CalcI/IndefiniteIntegrals.aspx" class="mm-link">Indefinite Integrals</a></li>
                <li><a href="/Classes/CalcI/ComputingIndefiniteIntegrals.aspx" class="mm-link">Computing Indefinite Integrals</a></li>
                <li><a href="/Classes/CalcI/SubstitutionRuleIndefinite.aspx" class="mm-link">Substitution Rule for Indefinite Integrals</a></li>
                <li><a href="/Classes/CalcI/SubstitutionRuleIndefinitePtII.aspx" class="mm-link">More Substitution Rule</a></li>
                <li><a href="/Classes/CalcI/AreaProblem.aspx" class="mm-link">Area Problem</a></li>
                <li><a href="/Classes/CalcI/DefnOfDefiniteIntegral.aspx" class="mm-link">Definition of the Definite Integral</a></li>
                <li><a href="/Classes/CalcI/ComputingDefiniteIntegrals.aspx" class="mm-link">Computing Definite Integrals</a></li>
                <li><a href="/Classes/CalcI/SubstitutionRuleDefinite.aspx" class="mm-link">Substitution Rule for Definite Integrals</a></li>
              </ul>
            </li>
            <li><a href="/Classes/CalcI/IntAppsIntro.aspx" class="mm-link">Applications of Integrals</a>
              <ul>
                <li><a href="/Classes/CalcI/AvgFcnValue.aspx" class="mm-link">Average Function Value</a></li>
                <li><a href="/Classes/CalcI/AreaBetweenCurves.aspx" class="mm-link">Area Between Curves</a></li>
                <li><a href="/Classes/CalcI/VolumeWithRings.aspx" class="mm-link">Volumes of Solids of Revolution / Method of Rings</a></li>
                <li><a href="/Classes/CalcI/VolumeWithCylinder.aspx" class="mm-link">Volumes of Solids of Revolution/Method of Cylinders</a></li>
                <li><a href="/Classes/CalcI/MoreVolume.aspx" class="mm-link">More Volume Problems</a></li>
                <li><a href="/Classes/CalcI/Work.aspx" class="mm-link">Work</a></li>
              </ul>
            </li>
            <li><a href="/Classes/CalcI/ExtrasIntro.aspx" class="mm-link">Extras</a>
              <ul>
                <li><a href="/Classes/CalcI/LimitProofs.aspx" class="mm-link">Proof of Various Limit Properties</a></li>
                <li><a href="/Classes/CalcI/DerivativeProofs.aspx" class="mm-link">Proof of Various Derivative Properties</a></li>
                <li><a href="/Classes/CalcI/ProofTrigDeriv.aspx" class="mm-link">Proof of Trig Limits</a></li>
                <li><a href="/Classes/CalcI/DerivativeAppsProofs.aspx" class="mm-link">Proofs of Derivative Applications Facts</a></li>
                <li><a href="/Classes/CalcI/ProofIntProp.aspx" class="mm-link">Proof of Various Integral Properties </a></li>
                <li><a href="/Classes/CalcI/Area_Volume_Formulas.aspx" class="mm-link">Area and Volume Formulas</a></li>
                <li><a href="/Classes/CalcI/TypesOfInfinity.aspx" class="mm-link">Types of Infinity</a></li>
                <li><a href="/Classes/CalcI/SummationNotation.aspx" class="mm-link">Summation Notation</a></li>
                <li><a href="/Classes/CalcI/ConstantofIntegration.aspx" class="mm-link">Constant of Integration</a></li>
              </ul>
            </li>
          </ul>
        </li>

        <li><a href="/Classes/CalcII/CalcII.aspx" class="mm-link">Calculus II</a>
          <ul>
            <li><a href="/Classes/CalcII/IntTechIntro.aspx" class="mm-link">Integration Techniques</a>
              <ul>
                <li><a href="/Classes/CalcII/IntegrationByParts.aspx" class="mm-link">Integration by Parts</a></li>
                <li><a href="/Classes/CalcII/IntegralsWithTrig.aspx" class="mm-link">Integrals Involving Trig Functions</a></li>
                <li><a href="/Classes/CalcII/TrigSubstitutions.aspx" class="mm-link">Trig Substitutions</a></li>
                <li><a href="/Classes/CalcII/PartialFractions.aspx" class="mm-link">Partial Fractions</a></li>
                <li><a href="/Classes/CalcII/IntegralsWithRoots.aspx" class="mm-link">Integrals Involving Roots</a></li>
                <li><a href="/Classes/CalcII/IntegralsWithQuadratics.aspx" class="mm-link">Integrals Involving Quadratics</a></li>
                <li><a href="/Classes/CalcII/IntegrationStrategy.aspx" class="mm-link">Integration Strategy</a></li>
                <li><a href="/Classes/CalcII/ImproperIntegrals.aspx" class="mm-link">Improper Integrals</a></li>
                <li><a href="/Classes/CalcII/ImproperIntegralsCompTest.aspx" class="mm-link">Comparison Test for Improper Integrals</a></li>
                <li><a href="/Classes/CalcII/ApproximatingDefIntegrals.aspx" class="mm-link">Approximating Definite Integrals</a></li>
              </ul>
            </li>
            <li><a href="/Classes/CalcII/IntAppsIntro.aspx" class="mm-link">Applications of Integrals</a>
              <ul>
                <li><a href="/Classes/CalcII/ArcLength.aspx" class="mm-link">Arc Length</a></li>
                <li><a href="/Classes/CalcII/SurfaceArea.aspx" class="mm-link">Surface Area</a></li>
                <li><a href="/Classes/CalcII/CenterOfMass.aspx" class="mm-link">Center of Mass</a></li>
                <li><a href="/Classes/CalcII/HydrostaticPressure.aspx" class="mm-link">Hydrostatic Pressure</a></li>
                <li><a href="/Classes/CalcII/Probability.aspx" class="mm-link">Probability</a></li>
              </ul>
            </li>
            <li><a href="/Classes/CalcII/ParametricIntro.aspx" class="mm-link">Parametric Equations and Polar Coordinates</a>
              <ul>
                <li><a href="/Classes/CalcII/ParametricEqn.aspx" class="mm-link">Parametric Equations and Curves</a></li>
                <li><a href="/Classes/CalcII/ParaTangent.aspx" class="mm-link">Tangents with Parametric Equations</a></li>
                <li><a href="/Classes/CalcII/ParaArea.aspx" class="mm-link">Area with Parametric Equations</a></li>
                <li><a href="/Classes/CalcII/ParaArcLength.aspx" class="mm-link">Arc Length with Parametric Equations</a></li>
                <li><a href="/Classes/CalcII/ParaSurfaceArea.aspx" class="mm-link">Surface Area with Parametric Equations</a></li>
                <li><a href="/Classes/CalcII/PolarCoordinates.aspx" class="mm-link">Polar Coordinates</a></li>
                <li><a href="/Classes/CalcII/PolarTangents.aspx" class="mm-link">Tangents with Polar Coordinates</a></li>
                <li><a href="/Classes/CalcII/PolarArea.aspx" class="mm-link">Area with Polar Coordinates</a></li>
                <li><a href="/Classes/CalcII/PolarArcLength.aspx" class="mm-link">Arc Length with Polar Coordinates</a></li>
                <li><a href="/Classes/CalcII/PolarSurfaceArea.aspx" class="mm-link">Surface Area with Polar Coordinates</a></li>
                <li><a href="/Classes/CalcII/ArcLength_SurfaceArea.aspx" class="mm-link">Arc Length and Surface Area Revisited</a></li>
              </ul>
            </li>
            <li><a href="/Classes/CalcII/SeriesIntro.aspx" class="mm-link">Series & Sequences</a>
              <ul>
                <li><a href="/Classes/CalcII/Sequences.aspx" class="mm-link">Sequences</a></li>
                <li><a href="/Classes/CalcII/MoreSequences.aspx" class="mm-link">More on Sequences</a></li>
                <li><a href="/Classes/CalcII/Series_Basics.aspx" class="mm-link">Series - The Basics</a></li>
                <li><a href="/Classes/CalcII/ConvergenceOfSeries.aspx" class="mm-link">Convergence/Divergence of Series</a></li>
                <li><a href="/Classes/CalcII/Series_Special.aspx" class="mm-link">Special Series</a></li>
                <li><a href="/Classes/CalcII/IntegralTest.aspx" class="mm-link">Integral Test</a></li>
                <li><a href="/Classes/CalcII/SeriesCompTest.aspx" class="mm-link">Comparison Test/Limit Comparison Test</a></li>
                <li><a href="/Classes/CalcII/AlternatingSeries.aspx" class="mm-link">Alternating Series Test</a></li>
                <li><a href="/Classes/CalcII/AbsoluteConvergence.aspx" class="mm-link">Absolute Convergence</a></li>
                <li><a href="/Classes/CalcII/RatioTest.aspx" class="mm-link">Ratio Test</a></li>
                <li><a href="/Classes/CalcII/RootTest.aspx" class="mm-link">Root Test</a></li>
                <li><a href="/Classes/CalcII/SeriesStrategy.aspx" class="mm-link">Strategy for Series</a></li>
                <li><a href="/Classes/CalcII/EstimatingSeries.aspx" class="mm-link">Estimating the Value of a Series</a></li>
                <li><a href="/Classes/CalcII/PowerSeries.aspx" class="mm-link">Power Series</a></li>
                <li><a href="/Classes/CalcII/PowerSeriesandFunctions.aspx" class="mm-link">Power Series and Functions</a></li>
                <li><a href="/Classes/CalcII/TaylorSeries.aspx" class="mm-link">Taylor Series</a></li>
                <li><a href="/Classes/CalcII/TaylorSeriesApps.aspx" class="mm-link">Applications of Series</a></li>
                <li><a href="/Classes/CalcII/BinomialSeries.aspx" class="mm-link">Binomial Series</a></li>
              </ul>
            </li>
            <li><a href="/Classes/CalcII/VectorsIntro.aspx" class="mm-link">Vectors</a>
              <ul>
                <li><a href="/Classes/CalcII/Vectors_Basics.aspx" class="mm-link">Vectors - The Basics</a></li>
                <li><a href="/Classes/CalcII/VectorArithmetic.aspx" class="mm-link">Vector Arithmetic</a></li>
                <li><a href="/Classes/CalcII/DotProduct.aspx" class="mm-link">Dot Product</a></li>
                <li><a href="/Classes/CalcII/CrossProduct.aspx" class="mm-link">Cross Product</a></li>
              </ul>
            </li>
            <li><a href="/Classes/CalcII/3DSpace.aspx" class="mm-link">3-Dimensional Space</a>
              <ul>
                <li><a href="/Classes/CalcII/3DCoords.aspx" class="mm-link">The 3-D Coordinate System</a></li>
                <li><a href="/Classes/CalcII/EqnsOfLines.aspx" class="mm-link">Equations of Lines</a></li>
                <li><a href="/Classes/CalcII/EqnsOfPlanes.aspx" class="mm-link">Equations of Planes</a></li>
                <li><a href="/Classes/CalcII/QuadricSurfaces.aspx" class="mm-link">Quadric Surfaces</a></li>
                <li><a href="/Classes/CalcII/MultiVrbleFcns.aspx" class="mm-link">Functions of Several Variables</a></li>
                <li><a href="/Classes/CalcII/VectorFunctions.aspx" class="mm-link">Vector Functions</a></li>
                <li><a href="/Classes/CalcII/VectorFcnsCalculus.aspx" class="mm-link">Calculus with Vector Functions</a></li>
                <li><a href="/Classes/CalcII/TangentNormalVectors.aspx" class="mm-link">Tangent, Normal and Binormal Vectors</a></li>
                <li><a href="/Classes/CalcII/VectorArcLength.aspx" class="mm-link">Arc Length with Vector Functions</a></li>
                <li><a href="/Classes/CalcII/Curvature.aspx" class="mm-link">Curvature</a></li>
                <li><a href="/Classes/CalcII/Velocity_Acceleration.aspx" class="mm-link">Velocity and Acceleration</a></li>
                <li><a href="/Classes/CalcII/CylindricalCoords.aspx" class="mm-link">Cylindrical Coordinates</a></li>
                <li><a href="/Classes/CalcII/SphericalCoords.aspx" class="mm-link">Spherical Coordinates</a></li>
              </ul>
            </li>
          </ul>
        </li>

        <li><a href="/Classes/CalcIII/CalcIII.aspx" class="mm-link">Calculus III</a>
          <ul>
            <li><a href="/Classes/CalcIII/3DSpace.aspx" class="mm-link">3-Dimensional Space</a>
              <ul>
                <li><a href="/Classes/CalcIII/3DCoords.aspx" class="mm-link">The 3-D Coordinate System</a></li>
                <li><a href="/Classes/CalcIII/EqnsOfLines.aspx" class="mm-link">Equations of Lines</a></li>
                <li><a href="/Classes/CalcIII/EqnsOfPlanes.aspx" class="mm-link">Equations of Planes</a></li>
                <li><a href="/Classes/CalcIII/QuadricSurfaces.aspx" class="mm-link">Quadric Surfaces</a></li>
                <li><a href="/Classes/CalcIII/MultiVrbleFcns.aspx" class="mm-link">Functions of Several Variables</a></li>
                <li><a href="/Classes/CalcIII/VectorFunctions.aspx" class="mm-link">Vector Functions</a></li>
                <li><a href="/Classes/CalcIII/VectorFcnsCalculus.aspx" class="mm-link">Calculus with Vector Functions</a></li>
                <li><a href="/Classes/CalcIII/TangentNormalVectors.aspx" class="mm-link">Tangent, Normal and Binormal Vectors</a></li>
                <li><a href="/Classes/CalcIII/VectorArcLength.aspx" class="mm-link">Arc Length with Vector Functions</a></li>
                <li><a href="/Classes/CalcIII/Curvature.aspx" class="mm-link">Curvature</a></li>
                <li><a href="/Classes/CalcIII/Velocity_Acceleration.aspx" class="mm-link">Velocity and Acceleration</a></li>
                <li><a href="/Classes/CalcIII/CylindricalCoords.aspx" class="mm-link">Cylindrical Coordinates</a></li>
                <li><a href="/Classes/CalcIII/SphericalCoords.aspx" class="mm-link">Spherical Coordinates</a></li>
              </ul>
            </li>
            <li><a href="/Classes/CalcIII/PartialDerivsIntro.aspx" class="mm-link">Partial Derivatives</a>
              <ul>
                <li><a href="/Classes/CalcIII/Limits.aspx" class="mm-link">Limits</a></li>
                <li><a href="/Classes/CalcIII/PartialDerivatives.aspx" class="mm-link">Partial Derivatives</a></li>
                <li><a href="/Classes/CalcIII/PartialDerivInterp.aspx" class="mm-link">Interpretations of Partial Derivatives</a></li>
                <li><a href="/Classes/CalcIII/HighOrderPartialDerivs.aspx" class="mm-link">Higher Order Partial Derivatives</a></li>
                <li><a href="/Classes/CalcIII/Differentials.aspx" class="mm-link">Differentials</a></li>
                <li><a href="/Classes/CalcIII/ChainRule.aspx" class="mm-link">Chain Rule</a></li>
                <li><a href="/Classes/CalcIII/DirectionalDeriv.aspx" class="mm-link">Directional Derivatives</a></li>
              </ul>
            </li>
            <li><a href="/Classes/CalcIII/PartialDerivAppsIntro.aspx" class="mm-link">Applications of Partial Derivatives</a>
              <ul>
                <li><a href="/Classes/CalcIII/TangentPlanes.aspx" class="mm-link">Tangent Planes and Linear Approximations</a></li>
                <li><a href="/Classes/CalcIII/GradientVectorTangentPlane.aspx" class="mm-link">Gradient Vector, Tangent Planes and Normal Lines</a></li>
                <li><a href="/Classes/CalcIII/RelativeExtrema.aspx" class="mm-link">Relative Minimums and Maximums</a></li>
                <li><a href="/Classes/CalcIII/AbsoluteExtrema.aspx" class="mm-link">Absolute Minimums and Maximums</a></li>
                <li><a href="/Classes/CalcIII/LagrangeMultipliers.aspx" class="mm-link">Lagrange Multipliers</a></li>
              </ul>
            </li>
            <li><a href="/Classes/CalcIII/MultipleIntegralsIntro.aspx" class="mm-link">Multiple Integrals</a>
              <ul>
                <li><a href="/Classes/CalcIII/DoubleIntegrals.aspx" class="mm-link">Double Integrals</a></li>
                <li><a href="/Classes/CalcIII/IteratedIntegrals.aspx" class="mm-link">Iterated Integrals</a></li>
                <li><a href="/Classes/CalcIII/DIGeneralRegion.aspx" class="mm-link">Double Integrals over General Regions</a></li>
                <li><a href="/Classes/CalcIII/DIPolarCoords.aspx" class="mm-link">Double Integrals in Polar Coordinates</a></li>
                <li><a href="/Classes/CalcIII/TripleIntegrals.aspx" class="mm-link">Triple Integrals</a></li>
                <li><a href="/Classes/CalcIII/TICylindricalCoords.aspx" class="mm-link">Triple Integrals in Cylindrical Coordinates</a></li>
                <li><a href="/Classes/CalcIII/TISphericalCoords.aspx" class="mm-link">Triple Integrals in Spherical Coordinates</a></li>
                <li><a href="/Classes/CalcIII/ChangeOfVariables.aspx" class="mm-link">Change of Variables</a></li>
                <li><a href="/Classes/CalcIII/SurfaceArea.aspx" class="mm-link">Surface Area</a></li>
                <li><a href="/Classes/CalcIII/Area_Volume.aspx" class="mm-link">Area and Volume Revisited</a></li>
              </ul>
            </li>
            <li><a href="/Classes/CalcIII/LineIntegralsIntro.aspx" class="mm-link">Line Integrals</a>
              <ul>
                <li><a href="/Classes/CalcIII/VectorFields.aspx" class="mm-link">Vector Fields</a></li>
                <li><a href="/Classes/CalcIII/LineIntegralsPtI.aspx" class="mm-link">Line Integrals - Part I</a></li>
                <li><a href="/Classes/CalcIII/LineIntegralsPtII.aspx" class="mm-link">Line Integrals - Part II</a></li>
                <li><a href="/Classes/CalcIII/LineIntegralsVectorFields.aspx" class="mm-link">Line Integrals of Vector Fields</a></li>
                <li><a href="/Classes/CalcIII/FundThmLineIntegrals.aspx" class="mm-link">Fundamental Theorem for Line Integrals</a></li>
                <li><a href="/Classes/CalcIII/ConservativeVectorField.aspx" class="mm-link">Conservative Vector Fields</a></li>
                <li><a href="/Classes/CalcIII/GreensTheorem.aspx" class="mm-link">Green's Theorem</a></li>
              </ul>
            </li>
            <li><a href="/Classes/CalcIII/SurfaceIntegralsIntro.aspx" class="mm-link">Surface Integrals</a>
              <ul>
                <li><a href="/Classes/CalcIII/CurlDivergence.aspx" class="mm-link">Curl and Divergence</a></li>
                <li><a href="/Classes/CalcIII/ParametricSurfaces.aspx" class="mm-link">Parametric Surfaces</a></li>
                <li><a href="/Classes/CalcIII/SurfaceIntegrals.aspx" class="mm-link">Surface Integrals</a></li>
                <li><a href="/Classes/CalcIII/SurfIntVectorField.aspx" class="mm-link">Surface Integrals of Vector Fields</a></li>
                <li><a href="/Classes/CalcIII/StokesTheorem.aspx" class="mm-link">Stokes' Theorem</a></li>
                <li><a href="/Classes/CalcIII/DivergenceTheorem.aspx" class="mm-link">Divergence Theorem</a></li>
              </ul>
            </li>
          </ul>
        </li>

        <li><a href="/Classes/DE/DE.aspx" class="mm-link">Differential Equations</a>
          <ul>
            <li><a href="/Classes/DE/IntroBasic.aspx" class="mm-link">Basic Concepts</a>
              <ul>
                <li><a href="/Classes/DE/Definitions.aspx" class="mm-link">Definitions</a></li>
                <li><a href="/Classes/DE/DirectionFields.aspx" class="mm-link">Direction Fields</a></li>
                <li><a href="/Classes/DE/FinalThoughts.aspx" class="mm-link">Final Thoughts</a></li>
              </ul>
            </li>
            <li><a href="/Classes/DE/IntroFirstOrder.aspx" class="mm-link">First Order DE's</a>
              <ul>
                <li><a href="/Classes/DE/Linear.aspx" class="mm-link">Linear Equations</a></li>
                <li><a href="/Classes/DE/Separable.aspx" class="mm-link">Separable Equations</a></li>
                <li><a href="/Classes/DE/Exact.aspx" class="mm-link">Exact Equations</a></li>
                <li><a href="/Classes/DE/Bernoulli.aspx" class="mm-link">Bernoulli Differential Equations</a></li>
                <li><a href="/Classes/DE/Substitutions.aspx" class="mm-link">Substitutions</a></li>
                <li><a href="/Classes/DE/IoV.aspx" class="mm-link">Intervals of Validity</a></li>
                <li><a href="/Classes/DE/Modeling.aspx" class="mm-link">Modeling with First Order DE's</a></li>
                <li><a href="/Classes/DE/EquilibriumSolutions.aspx" class="mm-link">Equilibrium Solutions</a></li>
                <li><a href="/Classes/DE/EulersMethod.aspx" class="mm-link">Euler's Method</a></li>
              </ul>
            </li>
            <li><a href="/Classes/DE/IntroSecondOrder.aspx" class="mm-link">Second Order DE's</a>
              <ul>
                <li><a href="/Classes/DE/SecondOrderConcepts.aspx" class="mm-link">Basic Concepts</a></li>
                <li><a href="/Classes/DE/RealRoots.aspx" class="mm-link">Real & Distinct Roots</a></li>
                <li><a href="/Classes/DE/ComplexRoots.aspx" class="mm-link">Complex Roots</a></li>
                <li><a href="/Classes/DE/RepeatedRoots.aspx" class="mm-link">Repeated Roots</a></li>
                <li><a href="/Classes/DE/ReductionofOrder.aspx" class="mm-link">Reduction of Order</a></li>
                <li><a href="/Classes/DE/FundamentalSetsofSolutions.aspx" class="mm-link">Fundamental Sets of Solutions</a></li>
                <li><a href="/Classes/DE/Wronskian.aspx" class="mm-link">More on the  Wronskian</a></li>
                <li><a href="/Classes/DE/NonhomogeneousDE.aspx" class="mm-link">Nonhomogeneous Differential Equations</a></li>
                <li><a href="/Classes/DE/UndeterminedCoefficients.aspx" class="mm-link">Undetermined Coefficients</a></li>
                <li><a href="/Classes/DE/VariationofParameters.aspx" class="mm-link">Variation of Parameters</a></li>
                <li><a href="/Classes/DE/Vibrations.aspx" class="mm-link">Mechanical Vibrations</a></li>
              </ul>
            </li>
            <li><a href="/Classes/DE/LaplaceIntro.aspx" class="mm-link">Laplace Transforms</a>
              <ul>
                <li><a href="/Classes/DE/LaplaceDefinition.aspx" class="mm-link">The Definition</a></li>
                <li><a href="/Classes/DE/LaplaceTransforms.aspx" class="mm-link">Laplace Transforms</a></li>
                <li><a href="/Classes/DE/InverseTransforms.aspx" class="mm-link">Inverse Laplace Transforms</a></li>
                <li><a href="/Classes/DE/StepFunctions.aspx" class="mm-link">Step Functions</a></li>
                <li><a href="/Classes/DE/IVPWithLaplace.aspx" class="mm-link">Solving IVP's with Laplace Transforms</a></li>
                <li><a href="/Classes/DE/IVPWithNonConstantCoefficient.aspx" class="mm-link">Nonconstant Coefficient IVP's</a></li>
                <li><a href="/Classes/DE/IVPWithStepFunction.aspx" class="mm-link">IVP's With Step Functions</a></li>
                <li><a href="/Classes/DE/DiracDeltaFunction.aspx" class="mm-link">Dirac Delta Function</a></li>
                <li><a href="/Classes/DE/ConvolutionIntegrals.aspx" class="mm-link">Convolution Integrals</a></li>
                <li><a href="/Classes/DE/Laplace_Table.aspx" class="mm-link">Table Of Laplace Transforms</a></li>
              </ul>
            </li>
            <li><a href="/Classes/DE/SystemsIntro.aspx" class="mm-link">Systems of DE's</a>
              <ul>
                <li><a href="/Classes/DE/LA_Systems.aspx" class="mm-link">Review : Systems of Equations</a></li>
                <li><a href="/Classes/DE/LA_Matrix.aspx" class="mm-link">Review : Matrices & Vectors</a></li>
                <li><a href="/Classes/DE/LA_Eigen.aspx" class="mm-link">Review : Eigenvalues & Eigenvectors</a></li>
                <li><a href="/Classes/DE/SystemsDE.aspx" class="mm-link">Systems of Differential Equations</a></li>
                <li><a href="/Classes/DE/SolutionsToSystems.aspx" class="mm-link">Solutions to Systems</a></li>
                <li><a href="/Classes/DE/PhasePlane.aspx" class="mm-link">Phase Plane</a></li>
                <li><a href="/Classes/DE/RealEigenvalues.aspx" class="mm-link">Real Eigenvalues</a></li>
                <li><a href="/Classes/DE/ComplexEigenvalues.aspx" class="mm-link">Complex Eigenvalues</a></li>
                <li><a href="/Classes/DE/RepeatedEigenvalues.aspx" class="mm-link">Repeated Eigenvalues</a></li>
                <li><a href="/Classes/DE/NonhomogeneousSystems.aspx" class="mm-link">Nonhomogeneous Systems</a></li>
                <li><a href="/Classes/DE/SystemsLaplace.aspx" class="mm-link">Laplace Transforms</a></li>
                <li><a href="/Classes/DE/SystemsModeling.aspx" class="mm-link">Modeling</a></li>
              </ul>
            </li>
            <li><a href="/Classes/DE/SeriesIntro.aspx" class="mm-link">Series Solutions to DE's</a>
              <ul>
                <li><a href="/Classes/DE/PowerSeries.aspx" class="mm-link">Review : Power Series</a></li>
                <li><a href="/Classes/DE/TaylorSeries.aspx" class="mm-link">Review : Taylor Series</a></li>
                <li><a href="/Classes/DE/SeriesSolutions.aspx" class="mm-link">Series Solutions</a></li>
                <li><a href="/Classes/DE/EulerEquations.aspx" class="mm-link">Euler Equations</a></li>
              </ul>
            </li>
            <li><a href="/Classes/DE/IntroHigherOrder.aspx" class="mm-link">Higher Order Differential Equations</a>
              <ul>
                <li><a href="/Classes/DE/HOBasicConcepts.aspx" class="mm-link">Basic Concepts for <em>n</em><sup>th</sup> Order Linear Equations</a></li>
                <li><a href="/Classes/DE/HOHomogeneousDE.aspx" class="mm-link">Linear Homogeneous Differential Equations</a></li>
                <li><a href="/Classes/DE/HOUndeterminedCoeff.aspx" class="mm-link">Undetermined Coefficients</a></li>
                <li><a href="/Classes/DE/HOVariationOfParam.aspx" class="mm-link">Variation of Parameters</a></li>
                <li><a href="/Classes/DE/HOLaplaceTransforms.aspx" class="mm-link">Laplace Transforms</a></li>
                <li><a href="/Classes/DE/HOSystems.aspx" class="mm-link">Systems of Differential Equations</a></li>
                <li><a href="/Classes/DE/HOSeries.aspx" class="mm-link">Series Solutions</a></li>
              </ul>
            </li>
            <li><a href="/Classes/DE/IntroBVP.aspx" class="mm-link">Boundary Value Problems &amp; Fourier Series</a>
              <ul>
                <li><a href="/Classes/DE/BoundaryValueProblem.aspx" class="mm-link">Boundary Value Problems</a></li>
                <li><a href="/Classes/DE/BVPEvals.aspx" class="mm-link">Eigenvalues and Eigenfunctions</a></li>
                <li><a href="/Classes/DE/PeriodicOrthogonal.aspx" class="mm-link">Periodic Functions &amp; Orthogonal Functions</a></li>
                <li><a href="/Classes/DE/FourierSineSeries.aspx" class="mm-link">Fourier Sine Series</a></li>
                <li><a href="/Classes/DE/FourierCosineSeries.aspx" class="mm-link">Fourier Cosine Series</a></li>
                <li><a href="/Classes/DE/FourierSeries.aspx" class="mm-link">Fourier Series</a></li>
                <li><a href="/Classes/DE/ConvergenceFourierSeries.aspx" class="mm-link">Convergence of Fourier Series</a></li>
              </ul>
            </li>
            <li><a href="/Classes/DE/IntroPDE.aspx" class="mm-link">Partial Differential Equations </a>
              <ul>
                <li><a href="/Classes/DE/TheHeatEquation.aspx" class="mm-link">The Heat Equation</a></li>
                <li><a href="/Classes/DE/TheWaveEquation.aspx" class="mm-link">The Wave Equation</a></li>
                <li><a href="/Classes/DE/PDETerminology.aspx" class="mm-link">Terminology</a></li>
                <li><a href="/Classes/DE/SeparationofVariables.aspx" class="mm-link">Separation of Variables</a></li>
                <li><a href="/Classes/DE/SolvingHeatEquation.aspx" class="mm-link">Solving the Heat Equation</a></li>
                <li><a href="/Classes/DE/HeatEqnNonZero.aspx" class="mm-link">Heat Equation with Non-Zero Temperature Boundaries</a></li>
                <li><a href="/Classes/DE/LaplacesEqn.aspx" class="mm-link">Laplace's Equation</a></li>
                <li><a href="/Classes/DE/VibratingString.aspx" class="mm-link">Vibrating String</a></li>
                <li><a href="/Classes/DE/PDESummary.aspx" class="mm-link">Summary of Separation of Variables</a></li>
              </ul>
            </li>
          </ul>
        </li>

        <li><span>Extras</span></li>
        <li><a href="/Extras/AlgebraTrigReview/AlgebraTrig.aspx" class="mm-link">Algebra &amp; Trig Review</a>
          <ul>
            <li><a href="/Extras/AlgebraTrigReview/AlgebraIntro.aspx" class="mm-link">Algebra</a>
              <ul>
                <li><a href="/Extras/AlgebraTrigReview/Exponents.aspx" class="mm-link">Exponents </a></li>
                <li><a href="/Extras/AlgebraTrigReview/AbsoluteValue.aspx" class="mm-link">Absolute Value</a></li>
                <li><a href="/Extras/AlgebraTrigReview/Radicals.aspx" class="mm-link">Radicals</a></li>
                <li><a href="/Extras/AlgebraTrigReview/Rationalizing.aspx" class="mm-link">Rationalizing </a></li>
                <li><a href="/Extras/AlgebraTrigReview/Functions.aspx" class="mm-link">Functions </a></li>
                <li><a href="/Extras/AlgebraTrigReview/MultPoly.aspx" class="mm-link">Multiplying Polynomials</a></li>
                <li><a href="/Extras/AlgebraTrigReview/Factoring.aspx" class="mm-link">Factoring</a></li>
                <li><a href="/Extras/AlgebraTrigReview/SimpRatExp.aspx" class="mm-link">Simplifying Rational Expressions</a></li>
                <li><a href="/Extras/AlgebraTrigReview/Graphing.aspx" class="mm-link">Graphing and Common Graphs</a></li>
                <li><a href="/Extras/AlgebraTrigReview/SolveEqnPtI.aspx" class="mm-link">Solving Equations, Part I</a></li>
                <li><a href="/Extras/AlgebraTrigReview/SolveEqnPtII.aspx" class="mm-link">Solving Equations, Part II</a></li>
                <li><a href="/Extras/AlgebraTrigReview/SolveSystems.aspx" class="mm-link">Solving Systems of Equations</a></li>
                <li><a href="/Extras/AlgebraTrigReview/SolveIneq.aspx" class="mm-link">Solving Inequalities</a></li>
                <li><a href="/Extras/AlgebraTrigReview/SolveAbsValue.aspx" class="mm-link">Absolute Value Equations and Inequalities</a></li>
              </ul>
            </li>
            <li><a href="/Extras/AlgebraTrigReview/TrigIntro.aspx" class="mm-link">Trigonometry</a>
              <ul>
                <li><a href="/Extras/AlgebraTrigReview/TrigFunctions.aspx" class="mm-link">Trig Function Evaluation</a></li>
                <li><a href="/Extras/AlgebraTrigReview/TrigGraphs.aspx" class="mm-link">Graphs of Trig Functions</a></li>
                <li><a href="/Extras/AlgebraTrigReview/TrigFormulas.aspx" class="mm-link">Trig Formulas</a></li>
                <li><a href="/Extras/AlgebraTrigReview/SolveTrigEqn.aspx" class="mm-link">Solving Trig Equations</a></li>
                <li><a href="/Extras/AlgebraTrigReview/InverseTrig.aspx" class="mm-link">Inverse Trig Functions</a></li>
              </ul>
            </li>
            <li><a href="/Extras/AlgebraTrigReview/ExpLogIntro.aspx" class="mm-link">Exponentials & Logarithms</a>
              <ul>
                <li><a href="/Extras/AlgebraTrigReview/ExponentialFcns.aspx" class="mm-link">Basic Exponential Functions</a></li>
                <li><a href="/Extras/AlgebraTrigReview/LogarithmFcns.aspx" class="mm-link">Basic Logarithm Functions</a></li>
                <li><a href="/Extras/AlgebraTrigReview/LogProperties.aspx" class="mm-link">Logarithm Properties</a></li>
                <li><a href="/Extras/AlgebraTrigReview/SimpLogs.aspx" class="mm-link">Simplifying Logarithms</a></li>
                <li><a href="/Extras/AlgebraTrigReview/SolveExpEqn.aspx" class="mm-link">Solving Exponential Equations</a></li>
                <li><a href="/Extras/AlgebraTrigReview/SolveLogEqn.aspx" class="mm-link">Solving Logarithm Equations</a></li>
              </ul>
            </li>
          </ul>
        </li>

        <li><a href="/Extras/CommonErrors/CommonMathErrors.aspx" class="mm-link">Common Math Errors</a>
          <ul>
            <li><a href="/Extras/CommonErrors/GeneralErrors.aspx" class="mm-link">General Errors</a>
            </li>
            <li><a href="/Extras/CommonErrors/AlgebraErrors.aspx" class="mm-link">Algebra Errors</a>
            </li>
            <li><a href="/Extras/CommonErrors/TrigErrors.aspx" class="mm-link">Trig Errors</a>
            </li>
            <li><a href="/Extras/CommonErrors/CommonErrors.aspx" class="mm-link">Common Errors</a>
            </li>
            <li><a href="/Extras/CommonErrors/CalculusErrors.aspx" class="mm-link">Calculus Errors</a>
            </li>
          </ul>
        </li>

        <li><a href="/Extras/ComplexPrimer/ComplexNumbers.aspx" class="mm-link">Complex Number Primer</a>
          <ul>
            <li><a href="/Extras/ComplexPrimer/Definition.aspx" class="mm-link">The Definition</a>
            </li>
            <li><a href="/Extras/ComplexPrimer/Arithmetic.aspx" class="mm-link">Arithmetic</a>
            </li>
            <li><a href="/Extras/ComplexPrimer/ConjugateModulus.aspx" class="mm-link">Conjugate and Modulus</a>
            </li>
            <li><a href="/Extras/ComplexPrimer/Forms.aspx" class="mm-link">Polar and Exponential Forms</a>
            </li>
            <li><a href="/Extras/ComplexPrimer/Roots.aspx" class="mm-link">Powers and Roots</a>
            </li>
          </ul>
        </li>

        <li><a href="/Extras/StudyMath/HowToStudyMath.aspx" class="mm-link">How To Study Math</a>
          <ul>
            <li><a href="/Extras/StudyMath/GeneralTips.aspx" class="mm-link">General Tips</a>
            </li>
            <li><a href="/Extras/StudyMath/TakingNotes.aspx" class="mm-link">Taking Notes</a>
            </li>
            <li><a href="/Extras/StudyMath/GettingHelp.aspx" class="mm-link">Getting Help</a>
            </li>
            <li><a href="/Extras/StudyMath/Homework.aspx" class="mm-link">Doing Homework</a>
            </li>
            <li><a href="/Extras/StudyMath/ProblemSolving.aspx" class="mm-link">Problem Solving</a>
            </li>
            <li><a href="/Extras/StudyMath/StudyForExam.aspx" class="mm-link">Studying For an Exam</a>
            </li>
            <li><a href="/Extras/StudyMath/TakingExam.aspx" class="mm-link">Taking an Exam</a>
            </li>
            <li><a href="/Extras/StudyMath/Errors.aspx" class="mm-link">Learn From Your Errors</a>
            </li>
          </ul>
        </li>

        <li><span>Misc Links</span></li>
        <li><a href="/contact.aspx" class="mm-link">Contact Me</a></li>
        <li><a href="/links.aspx" class="mm-link">Links</a></li>
        <li><a href="/mathjax.aspx" class="mm-link">MathJax Help and Configuration</a></li>
        <li><a href="/mystudents.aspx" class="mm-link">My Students</a></li>
        <li><a href="/privacy.aspx" class="mm-link">Privacy Statement</a></li>
        <li><a href="/help.aspx" class="mm-link">Site Help & FAQ</a></li>
        <li><a href="/terms.aspx" class="mm-link">Terms of Use</a></li>
      </ul>
    </nav>



    <div class="top-info-bar">
      <span id="mobile-title" class="mobile-header-title header-title">Paul's Online Notes</span>
      <br />
      <span class="top-menu-breadcrumb">
        <a href="/" id="breadcrumb_home_link" title="Go to Main Page">Home</a>
        <span id="breadcrumb_h_b_sep_span">/ </span>
        <a href="/Classes/CalcII/CalcII.aspx" id="breadcrumb_book_link" title="Go to Book Introduction">Calculus II</a>
        
        <span id="breadcrumb_b_c_sep_span">/ </span>
        <a href="/Classes/CalcII/IntAppsIntro.aspx" id="breadcrumb_chapter_link" title="Go to Chapter Introduction">Applications of Integrals</a>
        
        <span id="breadcrumb_section_span"> / Hydrostatic Pressure and Force</span>
      </span>

    </div>

    <div id="nav_links" class="top-nav-bar">
      
      <span id="nav_current_notes">Notes</span>
      <a href="/Problems/CalcII/HydrostaticPressure.aspx" id="nav_links_practice" title="Go to Practice Problems for current topic.">Practice<span class="nav_desktop_extra"> Problems</span></a>
      
      <a href="/ProblemsNS/CalcII/HydrostaticPressure.aspx" id="nav_links_asgn" title="Go to Assignment Problems for current topic.">Assignment<span class="nav_desktop_extra">  Problems</span></a>
      
    </div>

    <div class="header-divider"></div>

    <div class="content">  
      
      
      <span id="SHLink_NoteMobile" class="SH-Link content-note-link-mobile">Show Mobile Notice</span>
      <span id="SHImg_NoteMobile" class="fas fa-caret-right SH-padding content-note-link-mobile" aria-hidden="true"></span>
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      


      <span id="SHALink_S_Note" class="SH-Link SH-Hide SH-Bracket">Show All Notes</span>&nbsp;<span id="SHALink_H_Note" class="SH-Link SH-Hide SH-Bracket">Hide All Notes</span>
      
      
      <div id="SHObj_NoteMobile" class="content-note-container content-note-container-mobile">
        <div class="content-note-header">Mobile Notice</div>
        <div class="content-note">You appear to be on a device with a "narrow" screen width (<em>i.e.</em> you are probably on a mobile phone).  Due to the nature of the mathematics on this site it is best views in landscape mode.  If your device is not in landscape mode many of the equations will run off the side of your device (should be able to scroll to see them) and some of the menu items will be cut off due to the narrow screen width.</div>
      </div>
      
      
      
      
      
      
      
      
      
      
      


      


  <form method="post" action="./HydrostaticPressure.aspx" id="ctl00">
<div class="aspNetHidden">
<input type="hidden" name="__VIEWSTATE" id="__VIEWSTATE" value="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" />
</div>

<div class="aspNetHidden">

	<input type="hidden" name="__VIEWSTATEGENERATOR" id="__VIEWSTATEGENERATOR" value="245E0519" />
</div>
    
    
    
    
    
    
    
    
    
    
    
    
  </form>

  <h3>Section 2-4 : Hydrostatic Pressure and Force</h3>

    
    <p>In this section we are going to submerge a vertical plate in water and we want to know the force that is exerted on the plate due to the pressure of the water.  This force is often called the hydrostatic force.</p>
    
    <p>There are two basic formulas that we’ll be using here.  First, if we are \(d\) meters below the surface then the hydrostatic pressure is given by,</p>
    
    
      \[P = \rho gd\]
    
    <p>where, \(\rho \) is the density of the fluid and \(g\) is the gravitational acceleration.  We are going to assume that the fluid in question is water and since we are going to be using the metric system these quantities become,</p>
    
      \[\rho  = 1000{\mbox{ kg/}}{{\mbox{m}}^{\mbox{3}}}\hspace{0.25in}\hspace{0.25in}g = 9.81{\mbox{ m/}}{{\mbox{s}}^{\mbox{2}}}\]
    
    <p>The second formula that we need is the following.  Assume that a constant pressure \(P\) is acting on a surface with area \(A\).  Then the hydrostatic force that acts on the area is,</p>
    
    
        \[F = PA\]
    
    <p>Note that we won’t be able to find the hydrostatic force on a vertical plate using this formula since the pressure will vary with depth and hence will not be constant as required by this formula.  We will however need this for our work.</p>
    
    <p>The best way to see how these problems work is to do an example or two.</p>
    <a class="anchor" name="IntApps_Hydro_Ex1"></a>
  <div class="example">
    <span class="example-title">Example 1</span> Determine the hydrostatic force on the following triangular plate that is submerged in water as shown.
          
            <div class="center-div"><img alt="The plate is a triangle whose base is horizontal and at the water’s surface.  The point of the triangle is pointed directly down into the water and is directly under the middle of the base.  The length of the base is given as 6 meters and the height of the triangle is given as 4 meters." height="200" src="HydrostaticPressure_Files/image001.gif" width="200" /></div>
    <div class="example-content">
      <span id="SHLink_Soln1" class="SH-Link soln-title">Show Solution</span> <span id="SHImg_Soln1" class="fas fa-caret-right" aria-hidden="true"></span>
      <div id="SHObj_Soln1" class="soln-content">
        <p>The first thing to do here is set up an axis system.  So, let’s redo the sketch above with the following axis system added in.</p>
          
            <div class="center-div"><img alt="This sketch is almost identical to the sketch in the problem statement with a couple of exceptions.  First, the lengths have been removed and, more importantly, an x-axis has been added that starts in the middle of the base and goes straight down through the lower point of the triangle.  It is also acknowledged that the point will occur at a value of x=4 on the axis." height="200" src="HydrostaticPressure_Files/image002.gif" width="200" /></div>
          
          <p>So, we are going to orient the \(x\)-axis so that positive \(x\) is downward, \(x = 0\) corresponds to the water surface and \(x = 4\) corresponds to the depth of the tip of the triangle.</p>
          
          <p>Next we break up the triangle into \(n\) horizontal strips each of equal width \(\Delta x\) and in each interval \(\left[ {{x_{i - 1}},{x_i}} \right]\) choose any point \(x_i^*\).  In order to make the computations easier we are going to make two assumptions about these strips.  First, we will ignore the fact that the ends are actually going to be slanted and assume the strips are rectangular.  If \(\Delta x\) is sufficiently small this will not affect our computations much.  Second, we will assume that \(\Delta x\) is small enough that the hydrostatic pressure on each strip is essentially constant.</p>
          
          <p>Below is a representative strip.</p>
          
            <div class="center-div"><img alt="This is a sketch of the triangular plate and there is a line bisecting the triangle drawn from the middle of the base straight down to the point of the triangle below it.  It is noted that the distance from this bisecting line to the edge of the base is 3 meters.  There is also a representative horizontal strip shown at about the midpoint of the triangle.  On the strip, the distance from the bisecting line and the edge of the strip is given as “a”.  The distance from the base of the triangle down to the strip is given as $x_{i}^{*}$ and the distance from the strip to the bottom point of the triangle is given as $4-x_{i}^{*}$." height="361" src="HydrostaticPressure_Files/image003.gif" width="400" /></div>

          <p>The height of this strip is \(\Delta x\) and the width is 2\(a\).  We can use similar triangles to determine \(a\) as follows,</p>
          
              \[\frac{3}{4} = \frac{a}{{4 - x_i^*}}\hspace{0.25in}\hspace{0.25in} \Rightarrow \hspace{0.25in}\hspace{0.25in}a = 3 - \frac{3}{4}x_i^*\]
          
          <p>Now, since we are assuming the pressure on this strip is constant, the pressure is given by,</p>
          
              \[{P_i} = \rho gd = 1000\left( {9.81} \right)x_i^* = 9810x_i^*\]

          <p>and the hydrostatic force on each strip is,</p>
          
            \[{F_i} = {P_i}\,A = {P_i}\left( {2a\Delta x} \right) = 9810x_i^*\left( 2 \right)\left( {3 - \frac{3}{4}x_i^*} \right)\Delta x = 19620x_i^*\left( {3 - \frac{3}{4}x_i^*} \right)\,\Delta x\]
          
          <p>The approximate hydrostatic force on the plate is then the sum of the forces on all the strips or,</p>
          
            \[F \approx \sum\limits_{i = 1}^n {19620x_i^*\left( {3 - \frac{3}{4}x_i^*} \right)} \,\Delta x\]
          
          <p>Taking the limit will get the exact hydrostatic force,</p>
          
            \[F = \mathop {\lim }\limits_{n \to \infty } \sum\limits_{i = 1}^n {19620x_i^*\left( {3 - \frac{3}{4}x_i^*} \right)} \,\Delta x\]
          
          <p>Using the <a href="/Classes/CalcI/DefnofDefiniteIntegral.aspx">definition of the definite integral</a> this is nothing more than,</p>
          
              \[F = \int_{{\,0}}^{{\,4}}{{19620\left( {3x - \frac{3}{4}{x^2}} \right)\,dx}}\]
          
          <p>The hydrostatic force is then,</p>
          
            \[\begin{align*}F &= \int_{{\,0}}^{{\,4}}{{19620\left( {3x - \frac{3}{4}{x^2}} \right)\,dx}}\\ &amp;  = \left. {19620\left( {\frac{3}{2}{x^2} - \frac{1}{4}{x^3}} \right)} \right|_0^4\\ &amp;  = 156960\,N\end{align*}\]
      </div>
    </div>
  </div>
    
    <p>Let’s take a look at another example.</p>
    <a class="anchor" name="IntApps_Hydro_Ex2"></a>
  <div class="example">
    <span class="example-title">Example 2</span> Find the hydrostatic force on a circular plate of radius 2 that is submerged 6 meters in the water.
    <div class="example-content">
      <span id="SHLink_Soln2" class="SH-Link soln-title">Show Solution</span> <span id="SHImg_Soln2" class="fas fa-caret-right" aria-hidden="true"></span>
      <div id="SHObj_Soln2" class="soln-content">
        <p>First, we’re going to assume that the top of the circular plate is 6 meters under the water.  Next, we will set up the axis system so that the origin of the axis system is at the center of the plate.  Setting the axis system up in this way will greatly simplify our work.</p>
          
          <p>Finally, we will again split up the plate into \(n\) horizontal strips each of width \(\Delta y\) and we’ll choose a point \(y_i^*\) from each strip.  We’ll also assume that the strips are rectangular again to help with the computations.  Here is a sketch of the setup.</p>
          
            <div class="center-div"><img alt="The water’s surface is shown at the top of the sketch.  Below the water’s surface is the circular plate and a standard xy-axis system is superimposed on the circle with the center of the circle at the origin of the axis system.  It is shown that the distance from the water’s surface and the top of the plate is 6 meters and the distance from the water’s surface to the x-axis (and hence the center of the plate) is 8 meters.  Also shown in the sketch is a representative strip that is located a distance of $d_{i}$ down from the surface of the water and is a distance of $y_{i}^{*}$ from the x-axis.  Also, the right half of the strip (i.e. from the y-axis to the edge of the strip on the edge of the circular plate) is shown to have a distance of $x=\sqrt{4-{{\left( y_{i}^{*} \right)}^{2}}}$." border="0" height="400" src="HydrostaticPressure_Files/image004.gif" width="400" /></div>
          
          <p>The depth below the water surface of each strip is,</p>
          
            \[{d_i} = 8 - y_i^*\]

          <p>and that in turn gives us the pressure on the strip,</p>
          
              \[{P_i} = \rho g{d_i} = 9810\left( {8 - y_i^*} \right)\]
          
          <p>The area of each strip is,</p>
          
              \[{A_i} = 2\sqrt {4 - {{\left( {y_i^*} \right)}^2}} \,\,\Delta y\]
          
          <p>The hydrostatic force on each strip is,</p>
          
            \[{F_i} = {P_i}{A_i} = 9810\left( {8 - y_i^*} \right)\left( 2 \right)\sqrt {4 - {{\left( {y_i^*} \right)}^2}} \,\,\Delta y\]
          
          <p>The total force on the plate is,</p>
          
            \[\begin{align*}F & = \mathop {\lim }\limits_{n \to \infty } \sum\limits_{i = 1}^n {19620\left( {8 - y_i^*} \right)\sqrt {4 - {{\left( {y_i^*} \right)}^2}} \,\,\Delta y} \\ &amp;  = 19620\int_{{\, - 2}}^{{\,2}}{{\left( {8 - y} \right)\sqrt {4 - {y^2}} \,dy}}\end{align*}\]
          
          <p>To do this integral we’ll need to split it up into two integrals.</p>
          
            \[F = 19620\int_{{\, - 2}}^{{\,2}}{{8\sqrt {4 - {y^2}} \,dy}} - 19620\int_{{\, - 2}}^{{\,2}}{{y\sqrt {4 - {y^2}} \,dy}}\]
          
          <p>The first integral requires the trig substitution \(y = 2\sin \theta \) and the second integral needs the substitution \(v = 4 - {y^2}\).  After using these substitutions we get,</p>
          
            \[\begin{align*}F & = 627840\int_{{\, - {\pi }/{2}\;}}^{{\,{\pi }/{2}\;}}{{{{\cos }^2}\theta \,d\theta }} + 9810\int_{{\,0}}^{{\,0}}{{\sqrt v \,dv}}\\ &amp;  = 313920\int_{{\, - {\pi }/{2}\;}}^{{\,{\pi }/{2}\;}}{{1 + \cos \left( {2\theta } \right)\,d\theta }} + 0\\ &amp;  = 313920\left. {\left( {\theta  + \frac{1}{2}\sin \left( {2\theta } \right)} \right)} \right|_{ - \frac{\pi }{2}}^{\frac{\pi }{2}}\\ &amp;  = 313920\pi \end{align*}\]
          
          <p>Note that after the substitution we know the second integral will be zero because the upper and lower limit is the same.</p>
      </div>
    </div>
  </div>
  


      



    </div>
    <!-- End of content div -->


    <div class="footer">
      <div class="footer-links">
        [<a href="/Contact.aspx">Contact Me</a>]&nbsp;[<a href="/MyStudents.aspx">My Students</a>]&nbsp;[<a href="/Privacy.aspx">Privacy Statement</a>]&nbsp;[<a href="/Help.aspx">Site Help &amp; FAQ</a>]&nbsp;[<a href="/Terms.aspx">Terms of Use</a>]
      </div>
      <div class="footer-dates">
        <div class="footer-copyright"><span id="lblCopyRight">&copy; 2003 - 2019 Paul Dawkins</span></div>
        <div class="footer-spacer"></div>
        <div class="footer-modified-date">Page Last Modified : <span id="lblModified">5/30/2018</span></div>
      </div>
      

    </div>
  </div>
  <!-- End of page div...  -->
</body>
</html>
