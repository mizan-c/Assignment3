/**
 * Kanishka Bansal
 * Mizanur Rahman
 */


package assignment3;


import assignment3.gui.GUI;
import assignment3.gui.GuiListener;

import java.io.IOException;
import java.io.OutputStreamWriter;


public class Main {
    public static void main(String[] args) {

        GUI gui=new GUI();
        gui.createGui();
        gui.titleLabel.setText("TCP Server");

        EchoServer echoServer = new EchoServer();

        echoServer.setServerListener(new EchoClient() {
            @Override
            public void onNewClientJoin(int id, String name) {
                gui.display("New Client joined:"+id+": "+name);
            }

            @Override
            public void onClientLeft(int id, String name) {
                gui.display("Client left:"+id+": "+name);
            }

            @Override
            public void onNewMessage(int id, String s) {
                gui.display("Message from "+id+": " + s);
            }
        });


        gui.setGuiListener(new GuiListener() {
            @Override
            public void onClickSend( String s) {

                OutputStreamWriter outputStreamWriter = echoServer.getOutputStreamById();

                if(outputStreamWriter==null){
                    System.out.println("Client need to send ID:id:name statement first");
                    return;
                }

                try {
                    outputStreamWriter.write(">> "+s + "\n"); //our client expect '\n' at the end
                    outputStreamWriter.flush();
                } catch (IOException e) {
                    e.printStackTrace();
                    gui.display(e.toString());
                }
            }
        });


        echoServer.startListening(5720);

    }
}
