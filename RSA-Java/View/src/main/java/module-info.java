module crypto.view {
	requires javafx.controls;
	requires javafx.fxml;

	requires org.controlsfx.controls;
	requires com.dlsc.formsfx;

	opens crypto.view to javafx.fxml;
	exports crypto.view;
}