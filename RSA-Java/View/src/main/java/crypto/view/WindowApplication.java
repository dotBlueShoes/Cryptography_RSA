package crypto.view;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class WindowApplication extends Application {
	@Override
	public void start(Stage stage) throws IOException {
		FXMLLoader fxmlLoader = new FXMLLoader(WindowApplication.class.getResource("hello-view.fxml"));
		Scene scene = new Scene(fxmlLoader.load(), 960, 680);
		stage.setTitle("RSA Cypher Algorithm");
		stage.setScene(scene);

		MainController controller = fxmlLoader.getController();
		// RSA 256 Generation call
		controller.refreshTextAreaParameters("a", "b", "c", "d", "e");

		stage.show();
	}

	public static void main(String[] args) {
		launch();
	}
}