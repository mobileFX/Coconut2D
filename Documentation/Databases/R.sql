SELECT
  *,
  group_concat(DISTINCT([NAME])) AS [Similar Devices]
FROM
(
   SELECT
       [Devices].[ID],
       [Devices].[Name],
       [Devices].[Brand],
       [Orientation].[NAME] AS [Orientation],
       [Devices].[PPI],
       [Devices].[Multiplier],

       [Devices].[LogicalPixelsWidth],
       [Devices].[LogicalPixelsHeight],
       [Devices].[PhysicalPixelsWidth],
       [Devices].[PhysicalPixelsHeight],

       [Devices].[AspectRatio] AS [Aspect Ratio],

       ([Devices].[LogicalPixelsWidth]+0.0) / [Devices].[LogicalPixelsHeight] AS [Aspect],

       CASE WHEN ([Devices].[LogicalPixelsWidth]+0.0) / [Devices].[LogicalPixelsHeight]<1.5
       THEN (([Devices].[LogicalPixelsWidth]+0.0)/480.0)
       ELSE (([Devices].[LogicalPixelsHeight]+0.0)/320.0)
       END AS [Upscale],

       CASE WHEN ([Devices].[LogicalPixelsWidth]+0.0) / [Devices].[LogicalPixelsHeight]>1.5
       THEN (([Devices].[LogicalPixelsWidth]+0.0)/480.0)
       ELSE (([Devices].[LogicalPixelsHeight]+0.0)/320.0)
       END AS [Overscale],

       [Devices].[LogicalPixelsWidth]/1366.0 AS [R]

   FROM [Devices]
       LEFT JOIN [Orientation] ON [Orientation].[ID] = [Devices].[GameOrientation]
       LEFT JOIN [OS] ON [OS].[ID] = [Devices].[OS]
       LEFT JOIN [CPU] ON [CPU].[ID] = [Devices].[CPU]
       LEFT JOIN [GPU] ON [GPU].[ID] = [Devices].[GPU]
)
WHERE R <=1
GROUP BY Brand,R,Multiplier
ORDER BY Brand,R,PPI
