using UnityEngine;
using System.Collections;

public class SimplePlayerMovement : MonoBehaviour {

    public float strafeVelocity = 10f;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
        if (Input.GetKey("left"))
        {
            Vector3 pos = this.transform.parent.position; //, rot = GetComponent<Rigidbody>().transform.forward;
            pos.x -= strafeVelocity * Time.deltaTime;
            this.transform.position = pos;
        }

        if (Input.GetKey("right"))
        {
            Vector3 pos = GetComponent<Rigidbody>().transform.position; //, rot = GetComponent<Rigidbody>().transform.forward;
            pos.x += strafeVelocity * Time.deltaTime;
            GetComponent<Rigidbody>().transform.position = pos;
        }
	}
}
