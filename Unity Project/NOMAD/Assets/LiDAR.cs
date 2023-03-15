using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LiDAR : MonoBehaviour
{
    public float angle = 0.0f;
    public bool autoRotate = true;
    public Material red;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        transform.rotation = Quaternion.Euler(0.0f, (float)angle, 0.0f);

        if(autoRotate){
            angle += 10.111f;
        }

        RaycastHit hit;
        if(Physics.Raycast(transform.position, transform.TransformDirection(Vector3.forward), out hit, 100)){
            Debug.DrawRay(transform.position, transform.TransformDirection(Vector3.forward) * hit.distance, Color.yellow);
            GameObject sphere = GameObject.CreatePrimitive(PrimitiveType.Sphere);
            sphere.transform.position = hit.point + new Vector3(0.0f, 2.0f, 0.0f);
            sphere.transform.localScale = new Vector3(0.1f,0.1f,0.1f);
            sphere.GetComponent<Renderer>().material = red;
        }
    }
}
