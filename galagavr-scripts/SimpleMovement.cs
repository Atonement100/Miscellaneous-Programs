using UnityEngine;
using System.Collections;

public class SimpleMovement : MonoBehaviour {

    float speed = 50f;

	// Use this for initialization
	void Start () {
        this.enabled = true;
	}
	
	// Update is called once per frame
	void Update () {
        Vector3 pos = GetComponent<Rigidbody>().transform.position; //, rot = GetComponent<Rigidbody>().transform.forward;
        pos.x += speed * Time.deltaTime;
       // pos.y = speed * Time.deltaTime;
        //pos.z = speed * Time.deltaTime;
        GetComponent<Rigidbody>().transform.position = pos;
    }
}
