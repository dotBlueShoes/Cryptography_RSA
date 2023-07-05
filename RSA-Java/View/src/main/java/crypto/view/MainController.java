package crypto.view;

import crypto.model.FileIO;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Node;
import javafx.scene.control.Alert;
import javafx.scene.control.TextArea;
import javafx.scene.image.Image;
import javafx.stage.FileChooser;

import java.io.File;

public class MainController {
	@FXML
	private TextArea textAreaP, textAreaQ, textAreaN, textAreaE, textAreaD, textAreaTextInput, textAreaTextOutput;

	private File inputFile, outputFile;

	private void createInformationDialog(
		final String title,
		final String header,
		final String content
	) {
		Alert alert = new Alert(Alert.AlertType.INFORMATION);
		alert.setTitle(title);
		alert.setHeaderText(header);
		alert.setContentText(content);
		alert.show();
	}

	public void refreshTextAreaParameters(
		final String pText,
		final String qText,
		final String nText,
		final String eText,
		final String dText
	) {
		textAreaP.setText(pText);
		textAreaQ.setText(qText);
		textAreaN.setText(nText);
		textAreaE.setText(eText);
		textAreaD.setText(dText);
	}

	// Because it's the default element, and it picks up by default
	//  it renders before textAreaP nodes and so on.
	final boolean isInitialized() {
		return textAreaP != null;
	}

	@FXML
	protected void onTab1() {
		if (isInitialized()) {
			// RSA GEN
			refreshTextAreaParameters("1", "1", "1", "1", "1");
		}
	}

	@FXML
	protected void onTab2() {
		// RSA GEN
		refreshTextAreaParameters("2", "2", "2", "2", "2");
	}

	@FXML
	protected void onTab3() {
		// RSA GEN
		refreshTextAreaParameters("3", "3", "3", "3", "3");
	}

	@FXML
	protected void onTab4() {
		// RSA GEN
		refreshTextAreaParameters("4", "4", "4", "4", "4");
	}

	@FXML
	protected void onFileEncryptClick() {
		if (inputFile != null && outputFile != null) {
			byte[] data = FileIO.ReadFileToBytes(inputFile);
			// ENCRYPTION ---
			FileIO.WriteBytesToFile(outputFile.getPath(), data);
			createInformationDialog("Information", "Success", "Successfully Encrypted");
		} else {
			createInformationDialog("Information", "Warning", "Selected invalid file paths");
		}
	}

	@FXML
	protected void onFileDecryptClick() {
		if (inputFile != null && outputFile != null) {
			byte[] data = FileIO.ReadFileToBytes(inputFile);
			// DECRYPTION ---
			FileIO.WriteBytesToFile(outputFile.getPath(), data);
			createInformationDialog("Information", "Success", "Successfully Decrypted");
		} else {
			createInformationDialog("Information", "Warning", "Selected invalid file paths");
		}
	}

	@FXML
	protected void onFileSelectInputClick(ActionEvent event) {
		FileChooser fileChooser = new FileChooser();
		fileChooser.setTitle("Select Input File");
		inputFile = fileChooser.showOpenDialog(((Node)event.getTarget()).getScene().getWindow());
	}

	@FXML
	protected void onFileSelectOutputClick(ActionEvent event) {
		FileChooser fileChooser = new FileChooser();
		fileChooser.setTitle("Select Output File");
		outputFile = fileChooser.showSaveDialog(((Node)event.getTarget()).getScene().getWindow());
	}

	@FXML
	protected void onTextEncryptClick() {
		String data = textAreaTextInput.getText();
		if (data.isEmpty()) {
			createInformationDialog("Information", "Warning", "No text to encrypt");
		} else {
			// Encode ---
			textAreaTextOutput.setText(data);
			createInformationDialog("Information", "Success", "Successfully Encrypted");
		}
	}

	@FXML
	protected void onTextDecryptClick() {
		String data = textAreaTextOutput.getText();
		if (data.isEmpty()) {
			createInformationDialog("Information", "Warning", "No text to decrypt");
		} else {
			// Decode ---
			textAreaTextInput.setText(data);
			createInformationDialog("Information", "Success", "Successfully Decrypted");
		}
	}
}