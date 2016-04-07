set GRAPHVIZ=D:\mobileFX\Projects\Software\Coconut\IDE\Studio\etc\3rd_party\graphviz\bin
set DIAGRAMS=D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Documentation\ClassDiagrams
set INPUT=D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Documentation\ClassDiagrams\Coconut2D.gv
set OUTPUT=D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Documentation\ClassDiagrams\Coconut2D.png
"%GRAPHVIZ%\dot.exe" -Tpng  -o"%OUTPUT%" "%INPUT%"
"%GRAPHVIZ%\dot.exe" -Tsvg  -o"%OUTPUT%.svg" "%INPUT%"
