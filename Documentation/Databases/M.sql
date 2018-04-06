SELECT

	'' as [Select],
	[Device List],
	cast([Physical W] as int) || 'x' || cast([Physical H] as int) AS [Resolution],
	[Multiplier],
    [Fit],
	[R],

	CASE
		WHEN [Fit]='Both' THEN round([Physical W]/480,4)
		WHEN [Fit]='Width' THEN round([Physical W]/480,4)
		WHEN [Fit]='Height' THEN round([Physical H]/320,4)
	END as [@x]

FROM
(

	SELECT
		group_concat(DISTINCT([NAME])) AS [Device List],
		COUNT(NAME) AS [Devices],
		[Logical W],
		[Logical H],
		[Multiplier],
		[Physical W],
		[Physical H],
	    [Fit],
	    [R],
		round([Logical W]/[Logical H], 4) AS [Aspect],
		[Width (pt)],
		[Height (pt)],
		[dpi],
		[Width (px)],
		[Height (px)],
		[Crop W (px)],
		[Crop H (px)],

		CASE
			WHEN [Width (px)] >= [Physical W] AND [Height (px)] >= [Physical H] THEN ''
			ELSE 'ERROR'
		END AS [Sanity]

	FROM
	(

		SELECT
			*,
			[Physical W] AS [Crop W (px)],
			[Physical H] AS [Crop H (px)],

			CASE WHEN ([Width (px)]-[Physical W]>=0) AND ([Height (px)]-[Physical H]>=0)
			THEN ''
			ELSE
				CASE WHEN ([Width (px)]-[Physical W]>=0)
				THEN cast([Height (px)]-[Physical H] AS TEXT) || 'px height'
				ELSE cast([Width (px)]-[Physical W] AS TEXT) || 'px width'
				END
			END AS [Export]

		FROM
		(
			-- RESULING PIXELS OF EXPORT STEP 1
			-- You export background now!

			SELECT
				*,
				[Width (pt)] * [Multiplier] AS [Width (px)],
				[Height (pt)] * [Multiplier] AS [Height (px)]

			FROM
			(
				-- EXPORT STEP 1: Image Size by R (best accuracy please)

				SELECT

					--1536 AS [Magic Width],
					--1024 AS [Magic Height],
					--1822 AS [Asimakis Width],
					--1618 AS [Asimakis Height],
					--2.0 AS [Magic Multiplier],
					--1366 AS [Safe W],
					--910 AS [Safe H],

					*,
					cast(1620.0 * [R] AS int) AS [Width (pt)],
					cast(1024.0 * [R] AS int) AS [Height (pt)],
					cast(144.0 * ([Multiplier]/2.0) as int) AS [dpi]

				FROM
				(
					-- CALCULATE EXPORT FACTOR [R]

					SELECT

						*,

						CASE
							WHEN [Logical W] / [Logical H] = 480.0 / 320.0 THEN 'Both'
							WHEN [Logical W] / 1620.0 > [Logical H] / 1024.0 THEN 'Height'
							ELSE 'Width'
						END AS [Fit],

						CASE
							WHEN [Logical W] / [Logical H] = 480.0 / 320.0 THEN round([Logical W] / 1366.0, 4)
							WHEN [Logical W] / 1620.0 > [Logical H] / 1024.0 THEN round([Logical W] / 1620.0, 4) + 0.0001
							ELSE round([Logical H] / 1024.0, 4)
						END AS [R]


						--CASE
						--	WHEN [Logical W] / [Logical H] = 480.0 / 320.0 THEN [Logical W] / 1366.0
						--	WHEN [Logical W] / 1620.0 > [Logical H] / 1024.0 THEN [Logical W] / 1620.0
						--	ELSE [Logical H] / 1024.0
						--END AS [R]

					FROM
					(
						-- CALCULATE REAL SCREEN ASPECT RATIO [Aspect]

						SELECT
						   [Devices].[Name],
						   [Devices].[Brand],

						   [Devices].[LogicalPixelsWidth]+0.0 AS [Logical W],
						   [Devices].[LogicalPixelsHeight]+0.0 AS [Logical H],

						   [Devices].[Multiplier],

						   [Devices].[PhysicalPixelsWidth]+0.0 AS [Physical W],
						   [Devices].[PhysicalPixelsHeight]+0.0 AS [Physical H]

						FROM [Devices]
						--WHERE (LogicalPixelsWidth  || 'x' || LogicalPixelsHeight) IN ('480x320', '1024x768', '1280x720', '1920x1080', '960x640', '568x320', '736x414')

					)
				)
			)
		)
	)
	GROUP BY R, Multiplier
	ORDER BY Devices DESC
)
WHERE [Logical W]>=380 AND [Logical H]>=320
ORDER BY [Logical W] * [Logical H]