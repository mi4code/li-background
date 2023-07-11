
#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include <gtk-layer-shell.h>
#include <vector>
#include <string>
#include <iostream>


/*
CMD options:
 no support for alternative switches
 no support for unnamed arguments
*/

bool cmd_arg_check (int argc, char* argv[], int min, int max, std::vector<char*> required, std::vector<char*> allowed){
	if (argc >= min and argc <= max) {
		for (int i=0; i<argc; i++){
			
			for (auto it = required.begin(); it != required.end(); ++it){
				if (strcmp(*it,argv[i])) {
					required.erase(it);
					break;
				}
			}
			
			if (argv[i] [0] == '-'){
				bool contained = false;
				for (auto it = allowed.begin(); it != allowed.end(); ++it){
					if (strcmp(*it,argv[i])) {
						contained = true;
					}
				}
				if (!contained) return false;
			}
			
		}
		
		if (required.size() == 0){
			return true;
		}
	}
	return false;
}

bool cmd_arg_present (int argc, char* argv[], char* name){
	
	for (int i=0; i<argc; i++){
		if (strcmp(argv[i],name) == 0) return true;
	}
	return false;	
}

int cmd_arg_intbool (int argc, char* argv[], char* name, int def=0){
	
	for (int i=0; i<argc; i++){
		if (strcmp(argv[i],name) == 0){
			if (i+1 < argc){
				if (argv[i+1] [0] != '-') {
					if (argv[i+1] == "none" or argv[i+1] == "NONE") return def;
					if (argv[i+1] == "true" or argv[i+1] == "TRUE") return true;
					if (argv[i+1] == "false" or argv[i+1] == "FALSE") return false;
					else return std::stoi(argv[i+1]);
				}
				else return def;
			}
			else return def;
		}	
	}
	return def;	
}

std::string cmd_arg_string (int argc, char* argv[], char* name, char* def=""){
	
	for (int i=0; i<argc; i++){
		//std::cout<<argv[i]<<" "<<name<<"\n";
		if (strcmp(argv[i],name) == 0){
			if (i+1 < argc){
				if (argv[i+1] [0] != '-') return argv[i+1]; 
				else return def;
			}
			else return def;
		}	
	}
	
	return def;	
}

std::string cmd_arg_filepath (int argc, char* argv[], char* name, char* def=""){
	
	std::string path = cmd_arg_string(argc,argv,name,def);
	
	if (path[0] == '.' and path[1] == '/') path = get_current_dir_name() + path.substr(1);
	
	return path;
}


int main (int argc, char* argv[]){
	
	if ( !cmd_arg_check(argc,argv, 0,5,{}, {"--display","--file","--help"}) ){
		std::cout<<"bad arguments - exiting (run 'li-background --help' to show help)";
		return -1;
	}
	
	if (cmd_arg_present(argc,argv, "--help")){
		std::cout<<"\n";
		std::cout<<"li-background \n";
		std::cout<<" (HTML background for wlroots based desktops) \n";
		std::cout<<" arguments: \n";
		std::cout<<"  --display <number> \n";
		std::cout<<"  --file </path/to/*.html> \n";
		std::cout<<"  --help \n";
		std::cout<<"\n";
		return -1;
	}	
	

	int fargc = 0;
	//char* fargv[1];
    gtk_init(&fargc, &argv);

    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	
    //gtk_window_set_title(GTK_WINDOW(window), "Fullscreen Webview");
    //gtk_window_set_default_size(GTK_WINDOW(window),200,200);
    //gtk_window_fullscreen(GTK_WINDOW(window))	
    //window->set_decorated(false);


    gtk_layer_init_for_window(GTK_WINDOW(window));
    gtk_layer_set_layer(GTK_WINDOW(window), GTK_LAYER_SHELL_LAYER_BACKGROUND);
    gtk_layer_set_monitor(GTK_WINDOW(window),  gdk_display_get_monitor(gdk_display_get_default(), cmd_arg_intbool(argc,argv, "--display", 0))  );
	
    gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_TOP, true);
    gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_BOTTOM, true);
    gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_LEFT, true);
    gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_RIGHT, true);

    gtk_layer_set_exclusive_zone(GTK_WINDOW(window), -1);	


    WebKitWebView* webview = WEBKIT_WEB_VIEW(webkit_web_view_new());
    // TODO: load file from string (or maybe not cos u cant access any external file)
    webkit_web_view_load_uri(webview, std::string("file://"+cmd_arg_filepath(argc,argv, "--file", "./background.html")).c_str() );
    // TODO: disable zooming/scrolling/selection (will be done in *.html)


    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(webview));
    gtk_widget_show_all(window);


    gtk_main();

    return 0;
}
