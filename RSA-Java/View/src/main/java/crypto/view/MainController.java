package crypto.view;

import crypto.model.FileIO;
import crypto.model.RSA;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Node;
import javafx.scene.control.Alert;
import javafx.scene.control.TextArea;
import javafx.scene.image.Image;
import javafx.stage.FileChooser;

import java.io.File;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;

public class MainController {
	@FXML
	private TextArea textAreaP, textAreaQ, textAreaN, textAreaE, textAreaD, textAreaTextInput, textAreaTextOutput;


	private final Charset defaultCharset = StandardCharsets.UTF_8; // UTF_16 ???
	private RSA.Type selectedRSA = RSA.Type.RSA256;
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
			// RSA 256 Generation call
			RSA.initialize(RSA.RSA256.testP, RSA.RSA256.testQ);
			refreshTextAreaParameters(RSA.p.toString(), RSA.q.toString(), RSA.n.toString(), RSA.e.toString(), RSA.d.toString());
			selectedRSA = RSA.Type.RSA256;
		}
	}

	@FXML
	protected void onTab2() {
		// RSA 256 Generation call
		RSA.initialize(RSA.RSA512.testP, RSA.RSA512.testQ);
		refreshTextAreaParameters(RSA.p.toString(), RSA.q.toString(), RSA.n.toString(), RSA.e.toString(), RSA.d.toString());
		selectedRSA = RSA.Type.RSA512;
	}

	@FXML
	protected void onTab3() {
		// RSA 256 Generation call
		RSA.initialize(RSA.RSA1024.testP, RSA.RSA1024.testQ);
		refreshTextAreaParameters(RSA.p.toString(), RSA.q.toString(), RSA.n.toString(), RSA.e.toString(), RSA.d.toString());
		selectedRSA = RSA.Type.RSA1024;
	}

	@FXML
	protected void onTab4() {
		// RSA 256 Generation call
		RSA.initialize(RSA.RSA2048.testP, RSA.RSA2048.testQ);
		refreshTextAreaParameters(RSA.p.toString(), RSA.q.toString(), RSA.n.toString(), RSA.e.toString(), RSA.d.toString());
		selectedRSA = RSA.Type.RSA2048;
	}

	@FXML
	protected void onFileEncryptClick() {
		if (inputFile != null && outputFile != null) {
			byte[] data = FileIO.ReadFileToBytes(inputFile);

			switch (selectedRSA) {
				default:
				case RSA256: {
					byte[] encrypted = RSA.encrypt(data, RSA.RSA256.blockSize);
					FileIO.WriteBytesToFile(outputFile.getPath(), encrypted);
				}
				case RSA512: {
					byte[] encrypted = RSA.encrypt(data, RSA.RSA256.blockSize);
					FileIO.WriteBytesToFile(outputFile.getPath(), encrypted);
				}
				case RSA1024: {
					byte[] encrypted = RSA.encrypt(data, RSA.RSA256.blockSize);
					FileIO.WriteBytesToFile(outputFile.getPath(), encrypted);
				}
				case RSA2048: {
					byte[] encrypted = RSA.encrypt(data, RSA.RSA256.blockSize);
					FileIO.WriteBytesToFile(outputFile.getPath(), encrypted);
				}
			}

			createInformationDialog("Information", "Success", "Successfully Encrypted");
		} else {
			createInformationDialog("Information", "Warning", "Selected invalid file paths");
		}
	}

	@FXML
	protected void onFileDecryptClick() {
		if (inputFile != null && outputFile != null) {
			byte[] data = FileIO.ReadFileToBytes(inputFile);

			switch (selectedRSA) {
				default:
				case RSA256: {
					byte[] decrypted = RSA.decrypt(data, RSA.RSA256.blockSize);
					FileIO.WriteBytesToFile(outputFile.getPath(), decrypted);
				}
				case RSA512: {
					byte[] decrypted = RSA.decrypt(data, RSA.RSA256.blockSize);
					FileIO.WriteBytesToFile(outputFile.getPath(), decrypted);
				}
				case RSA1024: {
					byte[] decrypted = RSA.decrypt(data, RSA.RSA256.blockSize);
					FileIO.WriteBytesToFile(outputFile.getPath(), decrypted);
				}
				case RSA2048: {
					byte[] decrypted = RSA.decrypt(data, RSA.RSA256.blockSize);
					FileIO.WriteBytesToFile(outputFile.getPath(), decrypted);
				}
			}

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
		String message = textAreaTextInput.getText();
		if (message.isEmpty()) {
			createInformationDialog("Information", "Warning", "No text to encrypt");
		} else {
			byte[] data = message.getBytes(defaultCharset);

			switch (selectedRSA) {
				default:
				case RSA256: {
					byte[] encrypted = RSA.encrypt(data, RSA.RSA256.blockSize);
					textAreaTextOutput.setText(new String(encrypted));
				}
				case RSA512: {
					byte[] encrypted = RSA.encrypt(data, RSA.RSA256.blockSize);
					textAreaTextOutput.setText(new String(encrypted));
				}
				case RSA1024: {
					byte[] encrypted = RSA.encrypt(data, RSA.RSA256.blockSize);
					textAreaTextOutput.setText(new String(encrypted));
				}
				case RSA2048: {
					byte[] encrypted = RSA.encrypt(data, RSA.RSA256.blockSize);
					textAreaTextOutput.setText(new String(encrypted));
				}
			}

			createInformationDialog("Information", "Success", "Successfully Encrypted");
		}
	}

	@FXML
	protected void onTextDecryptClick() {
		String message = textAreaTextOutput.getText();
		if (message.isEmpty()) {
			createInformationDialog("Information", "Warning", "No text to decrypt");
		} else {
			byte[] data = message.getBytes(defaultCharset);

			switch (selectedRSA) {
				default:
				case RSA256: {
					byte[] decrypted = RSA.decrypt(data, RSA.RSA256.blockSize);
					textAreaTextInput.setText(new String(decrypted));
				}
				case RSA512: {
					byte[] decrypted = RSA.decrypt(data, RSA.RSA256.blockSize);
					textAreaTextInput.setText(new String(decrypted));
				}
				case RSA1024: {
					byte[] decrypted = RSA.decrypt(data, RSA.RSA256.blockSize);
					textAreaTextInput.setText(new String(decrypted));
				}
				case RSA2048: {
					byte[] decrypted = RSA.decrypt(data, RSA.RSA256.blockSize);
					textAreaTextInput.setText(new String(decrypted));
				}
			}

			createInformationDialog("Information", "Success", "Successfully Decrypted");
		}
	}
}