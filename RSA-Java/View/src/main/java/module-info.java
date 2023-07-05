module crypto.view {
	requires javafx.controls;
	requires javafx.fxml;

	requires org.controlsfx.controls;
	requires com.dlsc.formsfx;
	requires crypto.model;

	opens crypto.view to javafx.fxml;
	exports crypto.view;
}