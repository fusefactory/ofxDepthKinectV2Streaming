#version 330

uniform sampler2DRect tex0;

#define M_PI 3.1415926535897932384626433832795

//type
uniform bool onlyDepth;

//Distance
uniform float near;
uniform float far;

uniform float lens;
uniform float edge;

//Crop
uniform float top;
uniform float bottom;
uniform float right;
uniform float left;
uniform float x, y;
uniform float scale;
uniform float keystone;
uniform float correction;
uniform float noiseT;
uniform float maxDistance;

uniform float kinectWidth;
uniform float kinectHeight;
uniform float kinectHalfWidth;
uniform float kinectHalfHeight;

const float low2 = 1.0;

float myFar;

in vec4 depth;
in vec2 vertTexCoord;

out vec4 outColor;

void crop(const vec2 pos){
    if ( pos.x < left || pos.x > right || pos.y < top || pos.y > bottom){
        discard;
    }
}

//from https://forum.unity.com/threads/round-not-supported-in-shaders.144316/
float approxRound(const float f){
    return floor(f) + 0.5;
}

float depthValue(vec2 pos){
    
    float valueTex = texture(tex0, vec2(approxRound(pos.x), approxRound(pos.y))).x;
    if(valueTex <= 0.05) valueTex = 1.0;    // ===========> IMPORTANT!!!
    float value = maxDistance * (1.0-valueTex); // depending on kinect recording: 1.0- needed if near staff are white.
    
    myFar = far * (1.0 -  correction * (cos(M_PI / 3.0 * (kinectHeight - pos.y) / kinectHeight) - 0.5));
    
    return clamp(low2 + (value - near) / (near - myFar), 0.0, 1.0);
}

void main(){
    vec2 pos = vertTexCoord.xy;
    
    crop(pos);                               //crop (top, bottom, left, right)
    
    float d = depthValue(pos);     //d is depth value for kinect

    if (d >= noiseT){
        discard;
    }
    else if (! onlyDepth){
        //edge detection
        int white = 0;
        int black = 0;
        int inc = 4;
        for(int ky = -inc; ky <= inc; ky+=inc){
            for(int kx = -inc; kx <= inc; kx+=inc){
                vec2 aux = vec2(pos.x+float(kx), pos.y+float(ky));
                float dd = clamp(low2 + (maxDistance*texture(tex0, aux).r - near) / (near - myFar), 0.0, 1.0);
//                if (dd < 0.01) {
//                    discard;
//                }
                
                if(dd > 0.01 && dd < noiseT && d - dd < edge){ // edge was = 0.05
//                if(dd > 0.01 && d - dd < edge){ // edge was = 0.05
                    white++;
                }
                else if (dd > 0.01  && ky < 0){
                    black++;
                }
            }
        }
        if(white > 1 && black > 1){// white > 4 && black < 2){
            //ok
        }
        else{
            d = 0.0;
        }
    }

    outColor = vec4(vec3(d,d,d), 1.0);
}
