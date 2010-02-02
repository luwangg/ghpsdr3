/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package jmonitor;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;

/**
 *
 * @author john
 */
public class Client {

    public Client(String server,int receiver) {
        if(server!=null) {
            this.server=server;
        }
        port=8000+(receiver*2);
        try {
            socket=new Socket(this.server,port);
            inputStream=socket.getInputStream();
            outputStream=socket.getOutputStream();

            System.err.println("opened client socket on port "+Integer.toString(port));
        } catch (UnknownHostException e) {
            System.err.println("Client: UnknownHost: "+server);
            System.exit(1);
        } catch (IOException e) {
            System.err.println("Client: IOException: "+e.getMessage());
            System.exit(1);
        }
    }

    private synchronized void sendCommand(String command) {
        byte[] buffer=new byte[32];
        byte[] commandBytes=command.getBytes();

        //System.err.println(command);
        
        for(int i=0;i<32;i++) {
            if(i<commandBytes.length) {
                buffer[i]=commandBytes[i];
            } else {
                buffer[i]=0;
            }
        }

        try {
            outputStream.write(buffer);
            outputStream.flush();
        } catch (IOException e) {
            System.err.println("sendCommand: IOException: "+e.getMessage());
            System.exit(1);
        }
    }

    public void close() {
        try {
            socket.close();
        } catch(IOException e) {
            // ignore error on close
        }
    }

    public void getSpectrum() {
        int bytes;
        byte[] buffer=new byte[48+SAMPLES];
        int j;
        if(socket!=null) {
            try {
                sendCommand("getSpectrum "+SAMPLES);
                bytes=inputStream.read(buffer);
                if(bytes==buffer.length) {
                    //System.err.println("getSpectrum: read "+Integer.toString(bytes)+" bytes");
                    // Strings sent with NULL terminator
                    //j = 0;
                    //while (buffer[j] != '\0')j++;
                    //frequency=new String(buffer,0,j);
                    //j=0;
                    //while(buffer[j+14]!='\0') j++;
                    //filterLow=new String(buffer,14,j);
                    //j=0;
                    //while(buffer[j+20]!='\0') j++;
                    //filterHigh=new String(buffer,20,j);
                    //j = 0;
                    //while (buffer[j+26] != '\0') j++;
                    //mode=new String(buffer,26,j);
                    j=0;
                    while(buffer[j+32]!='\0') j++;
                    sampleRate=new String(buffer,32,j);
                    j=0;
                    while(buffer[j+40]!='\0') j++;
                    meter=Integer.parseInt(new String(buffer,40,j));

                    for(int i=0;i<SAMPLES;i++) {
                        samples[i]=-(buffer[i+48]&0xFF)-30;
                    }
                } else {
                    System.err.println("read spectrum read "+Integer.toString(bytes)+" bytes");
                }
            } catch (IOException e) {
            }
        }
    }

    public float[] getSamples() {
        return samples;
    }

    public long getFrequency() {
        return frequency;
    }

    public int getMode() {
        return mode;
    }

    public String getStringMode() {
        return modes[mode];
    }

    public int getFilterLow() {
        return filterLow;
    }

    public int getFilterHigh() {
        return filterHigh;
    }

    public int getSampleRate() {
        return Integer.parseInt(sampleRate);
    }

    public void setFrequency(long frequency) {
        this.frequency=frequency;
        sendCommand("setFrequency "+frequency);
    }

    public void setFilter(int filterLow,int filterHigh) {
        this.filterLow=filterLow;
        this.filterHigh=filterHigh;
        sendCommand("setFilter "+filterLow+" "+filterHigh);
        System.err.println("setFilter "+filterLow+" "+filterHigh);
    }

    public void setMode(int mode) {
        this.mode=mode;
        sendCommand("setMode "+mode);
        System.err.println("setMode " + mode);
    }

    public int getMeter() {
        return meter-30;
    }

    public int getCWPitch() {
        return cwPitch;
    }

    private int port=8000;
    private String server="81.146.61.118";
    private Socket socket;

    private InputStream inputStream;
    private OutputStream outputStream;

    private static final int SAMPLES=480;
    private float[] samples=new float[SAMPLES];

    private long frequency;
    private int filterLow;
    private int filterHigh;
    private int mode;
    private String sampleRate;
    private int band;
    private int meter;

    private int cwPitch=600;

    public static final int modeLSB=0;
    public static final int modeUSB=1;
    public static final int modeDSB=2;
    public static final int modeCWL=3;
    public static final int modeCWU=4;
    public static final int modeFMN=5;
    public static final int modeAM=6;
    public static final int modeDIGU=7;
    public static final int modeSPEC=8;
    public static final int modeDIGL=9;
    public static final int modeSAM=10;
    public static final int modeDRM=11;

    private String[] modes={"LSB","USB","DSB","CWL","CWU","FMN","AM","DIGU","SPEC","DIGL","SAM","DRM"};
}
