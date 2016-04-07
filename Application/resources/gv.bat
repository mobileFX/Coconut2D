set GRAPHVIZ=D:\mobileFX\Projects\Software\Coconut\IDE\Studio\etc\3rd_party\graphviz\bin
set DIAGRAMS=D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\Application\resources
set INPUT=D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\Application\resources\Scratch1_FSM.gv
set OUTPUT=D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\Application\resources\Scratch1_FSM.png
"%GRAPHVIZ%\dot.exe" -Tpng  -o"%OUTPUT%" "%INPUT%"
"%GRAPHVIZ%\dot.exe" -Tsvg  -o"%OUTPUT%.svg" "%INPUT%"
