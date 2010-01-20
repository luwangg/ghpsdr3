/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * WaterfallPanel.java
 *
 * Created on 20-Jan-2010, 09:42:39
 */

package jmonitor;

import java.awt.Image;
import java.awt.event.MouseEvent;

/**
 *
 * @author john
 */
public class WaterfallPanel extends javax.swing.JPanel {

    /** Creates new form WaterfallPanel */
    public WaterfallPanel() {
        initComponents();
        pixels=new int[WIDTH*HEIGHT];
        for(int i=0;i<pixels.length;i++) {
            pixels[i]=255<<24;
        }
    }
    
    protected void paintComponent(java.awt.Graphics g) {
        Image waterfallImage=java.awt.Toolkit.getDefaultToolkit().createImage(new java.awt.image.MemoryImageSource(WIDTH,HEIGHT,pixels,0,WIDTH));
        g.drawImage(waterfallImage,0,0,null);
    }

    public void updateWaterfall(float[] samples,int filterLow,int filterHigh,int sampleRate) {

        this.filterLow=filterLow;
        this.filterHigh=filterHigh;

        // move the pixel array down
        System.arraycopy(pixels,0,pixels,WIDTH,(WIDTH*(HEIGHT-1)));

        // draw the new line
        for(int i=0;i<WIDTH;i++) {
            pixels[i]=calculatePixel(samples[i]);
        }

        this.repaint();
    }

    private int calculatePixel(float sample) {
        // simple gray scale
        int v=((int)sample-low)*255/(high-low);

        if(v<0) v=0;
        if(v>255) v=255;

        int pixel=(255<<24)+(v<<16)+(v<<8)+v;
        return pixel;
    }

    public void setClient(Client client) {
        this.client = client;
    }

    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        setPreferredSize(new java.awt.Dimension(480, 100));
        addMouseWheelListener(new java.awt.event.MouseWheelListener() {
            public void mouseWheelMoved(java.awt.event.MouseWheelEvent evt) {
                formMouseWheelMoved(evt);
            }
        });
        addMouseListener(new java.awt.event.MouseAdapter() {
            public void mousePressed(java.awt.event.MouseEvent evt) {
                formMousePressed(evt);
            }
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                formMouseClicked(evt);
            }
        });
        addMouseMotionListener(new java.awt.event.MouseMotionAdapter() {
            public void mouseDragged(java.awt.event.MouseEvent evt) {
                formMouseDragged(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 480, Short.MAX_VALUE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 100, Short.MAX_VALUE)
        );
    }// </editor-fold>//GEN-END:initComponents

    private void formMouseWheelMoved(java.awt.event.MouseWheelEvent evt) {//GEN-FIRST:event_formMouseWheelMoved
        //client.sendCommand("scrollFrequency "+Integer.toString(evt.getWheelRotation()*(client.getSampleRate()/WIDTH)));
        client.sendCommand("scrollFrequency "+Integer.toString(evt.getWheelRotation()*100));
    }//GEN-LAST:event_formMouseWheelMoved

    private void formMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_formMouseClicked
        int scrollAmount=(evt.getX() - (WIDTH / 2)) * (client.getSampleRate() / WIDTH);
        switch(evt.getButton()) {
            case MouseEvent.BUTTON1:
                // Left Button - move to center of filter
                if(filterHigh<0) {
                    client.sendCommand("scrollFrequency " + Integer.toString(scrollAmount + ((filterHigh - filterLow) / 2)));
                } else {
                    client.sendCommand("scrollFrequency " + Integer.toString(scrollAmount - ((filterHigh - filterLow) / 2)));
                }
                break;
            case MouseEvent.BUTTON3:
                // Right Button - move to cursor
                client.sendCommand("scrollFrequency " + Integer.toString(scrollAmount));
                break;
        }
    }//GEN-LAST:event_formMouseClicked

    private void formMouseDragged(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_formMouseDragged
        int increment=startX-evt.getX();
        client.sendCommand("scrollFrequency "+Integer.toString(increment*(client.getSampleRate()/WIDTH)));
        startX=evt.getX();
    }//GEN-LAST:event_formMouseDragged

    private void formMousePressed(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_formMousePressed
        startX=evt.getX();
    }//GEN-LAST:event_formMousePressed


    // Variables declaration - do not modify//GEN-BEGIN:variables
    // End of variables declaration//GEN-END:variables

    private static final int WIDTH=480;
    private static final int HEIGHT=100;

    private int low=-115;
    private int high=-75;

    private int pixels[];

    private Client client;

    private int filterLow;
    private int filterHigh;

    private int startX;

}
