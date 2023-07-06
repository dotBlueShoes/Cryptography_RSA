package crypto.view;

import crypto.model.RSA;
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
		{ // RSA 256 Generation call
			RSA.initialize(RSA.RSA256.testP, RSA.RSA256.testQ);
		}
		controller.refreshTextAreaParameters(RSA.p.toString(), RSA.q.toString(), RSA.n.toString(), RSA.e.toString(), RSA.d.toString());
		controller.lateInit();

		stage.show();
	}

	public static void main(String[] args) {
		launch();
	}
}