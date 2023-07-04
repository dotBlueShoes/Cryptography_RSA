package crypto.view;

import javafx.fxml.FXML;
import javafx.scene.control.TextArea;

public class MainController {
	@FXML
	private TextArea textAreaP, textAreaQ, textAreaN, textAreaE, textAreaD, textAreaTextInput, textAreaTextOutput;

	@FXML
	protected void onFileEncryptClick() {
		textAreaP.setText("A!");
	}

	@FXML
	protected void onFileDecryptClick() {
		textAreaP.setText("B!");
	}

	@FXML
	protected void onFileSelectInputClick() {
		textAreaP.setText("C!");
	}

	@FXML
	protected void onFileSelectOutputClick() {
		textAreaP.setText("D!");
	}

	@FXML
	protected void onTextEncryptClick() {
		textAreaP.setText("E!");
	}

	@FXML
	protected void onTextDecryptClick() {
		textAreaP.setText("F!");
	}
}