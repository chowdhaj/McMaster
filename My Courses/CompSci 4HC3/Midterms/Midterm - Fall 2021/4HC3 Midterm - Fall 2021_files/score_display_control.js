D2L.LE.Grades = D2L.LE.Grades || {};
D2L.LE.Grades.ScoreDisplayControl = D2L.LE.Grades.ScoreDisplayControl || {};

D2L.LE.Grades.ScoreDisplay = D2L.Class.extend({

	Construct: function () {
		arguments.callee.$.Construct.call(this);

		this.Symbol = '';
		this.Colour = '';
		this.Score = '';
		this.OutOf = '';
		this.ShowSymbol = false;
		this.ShowColour = false;
		this.ShowScore = false;
	},

	Deserialize: function (deserializer) {
		this.Symbol = deserializer.GetMember('Symbol');
		this.Colour = deserializer.GetMember('Colour');
		this.Score = deserializer.GetMember('Score');
		this.OutOf = deserializer.GetMember('OutOf');
		this.ShowSymbol = deserializer.GetMember('ShowSymbol');
		this.ShowColour = deserializer.GetMember('ShowColour');
		this.ShowScore = deserializer.GetMember('ShowScore');
	}
});

D2L.LE.Grades.ScoreDisplayControl.Refresh = function (hasScore, score, outOf, gradeId) {

	var callback = function (response) {

		if (response.GetResponseType() != D2L.Rpc.ResponseType.Success) {
			return;
		}

		var i;
		var scoreDisplay = response.GetResult(D2L.LE.Grades.ScoreDisplay);

		var scoreLabels = UI.GetControls('lblScore');
		for (i = 0; i < scoreLabels.length; i++) {
			scoreLabels[i].SetText(new D2L.LP.Text.IText(scoreDisplay.Score));
		}

		var outOfLabels = UI.GetControls('lblOutOf');
		for (i = 0; i < outOfLabels.length; i++) {
			outOfLabels[i].SetText(new D2L.LP.Text.IText(scoreDisplay.OutOf));
		}

		var pointsDisplayGroups = UI.GetControls('DG_Score');
		for (i = 0; i < pointsDisplayGroups.length; i++) {
			pointsDisplayGroups[i].SetIsDisplayed(scoreDisplay.ShowScore);
		}

		var symbolLabels = UI.GetControls('lblSymbol');
		for (i = 0; i < symbolLabels.length; i++) {
			symbolLabels[i].SetText(new D2L.LP.Text.IText(scoreDisplay.Symbol));
		}

		var symbolDisplayGroups = UI.GetControls('DG_Symbol');
		for (i = 0; i < symbolDisplayGroups.length; i++) {
			symbolDisplayGroups[i].SetIsDisplayed(scoreDisplay.ShowSymbol);
		}

		var separatorDisplayGroups = UI.GetControls('DG_Separator');
		for (i = 0; i < separatorDisplayGroups.length; i++) {
			separatorDisplayGroups[i].SetIsDisplayed(scoreDisplay.ShowScore && scoreDisplay.ShowSymbol);
		}

		var colourContainers = UI.GetControls('CNT_Dot');
		for (i = 0; i < colourContainers.length; i++) {
			colourContainers[0].SetBackgroundColour(scoreDisplay.Colour);
		}

		var colourDisplayGroups = UI.GetControls('DG_Colour');
		for (i = 0; i < colourDisplayGroups.length; i++) {
			colourDisplayGroups[i].SetIsDisplayed( scoreDisplay.ShowColour );
		}
	};

	D2L.Rpc.Create('GetScoreDisplayFromValues', callback, '/d2l/lms/grades/controls/score_display_control.d2l').Call(hasScore, score, outOf, gradeId);
};

D2L.LE.Grades.ScoreDisplayControl.ShowDisplayOverrideDialog = function (gradeId, refreshScoreDisplayFunction) {

	if (gradeId == 0) {
		var errorDialog = new D2L.Dialog.Error(UI.GetUniqueHtmlId(), new D2L.LP.Text.LangTerm('Grades.ScoreDisplayControl.errNoGradeToOverrideDisplaySettings'));
		errorDialog.Open();
		return;
	}

	var outerCallback = function (response) {
		if (response.GetType() == D2L.Dialog.ResponseType.Positive) {
			refreshScoreDisplayFunction();
		}

		response.GetDialog().Close();
	};

	var dialog = new D2L.Dialog('displayOverrideDialog');
	dialog.SetTitle(new D2L.LP.Text.LangTerm('Grades.ScoreDisplayControl.titDisplayOverrides'));
	dialog.AddPrimaryButton(D2L.Control.Button.Type.Save);
	dialog.AddSecondaryButton(D2L.Control.Button.Type.Cancel);
	dialog.SetCallback(outerCallback);
	dialog.SetSrc('/d2l/lms/grades/admin/manage/item_display_overrides_dialog.d2l', 'SaveDisplayOverridesCallback');
	dialog.SetSrcParam('gradeObjectId', gradeId);
	dialog.SetSize( 600, 310 );
	dialog.Open();
};