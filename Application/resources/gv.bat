set GRAPHVIZ=D:\mobileFX\Projects\Software\Coconut\IDE\Studio\etc\3rd_party\graphviz\bin
set DIAGRAMS=D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\Application\resources
set INPUT=D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\Application\resources\SlotGameEngine.gv
set OUTPUT=D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\Application\resources\SlotGameEngine
"%GRAPHVIZ%\dot.exe" -n -Tpng  -o"%OUTPUT%.png" "%INPUT%"
