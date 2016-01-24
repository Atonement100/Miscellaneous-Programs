using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class SpawnNewTarget : MonoBehaviour
{

    public GameObject enemy;
    public float spawnTime = 1f;
    public float unitSpeed = 10f;
    private Vector3 spawnArea; // = GetComponent<Collider>().bounds.size;


    // Use this for initialization
    void Start()
    {
        spawnArea = GetComponent<Collider>().bounds.extents;
        StartCoroutine(SpawnEnemy(3, spawnArea));
    }

    private IEnumerator SpawnEnemy(int NumToSpawn, Vector3 spawn)
    {
        float spawnShift;
        Vector3 spawnPoint;

        while (true)
        {
            var dimInfo = getMaxDim(spawnArea);

            spawnShift = Random.Range(-dimInfo.dimension, dimInfo.dimension);
            spawnPoint = GetComponent<Collider>().bounds.center + makeShiftVector(spawnShift, dimInfo.position);
            yield return new WaitForSeconds(spawnTime); // wait half a second

            for (int i = 0; i < NumToSpawn; i++)
            {
                Instantiate(enemy, spawnPoint, new Quaternion(0, 0.25f, 0, 0.25f));
                yield return new WaitForSeconds(.2f);
            }
        }
    }

    struct DimInfo
    {
        public float dimension;
        public int position;

    }

    private DimInfo getMaxDim(Vector3 dims)
    {
        var dimInfo = new DimInfo { dimension = 0, position = 0 };

        if (dims.x >= dims.y && dims.x >= dims.z)
        {
            dimInfo.dimension = dims.x;
            dimInfo.position = 0;
        }
        else if (dims.y >= dims.x && dims.y >= dims.z)
        {
            dimInfo.dimension = dims.y;
            dimInfo.position = 1;
        }
        else
        {
            dimInfo.dimension = dims.z;
            dimInfo.position = 2;
        }

        return dimInfo;
    }

    private Vector3 makeShiftVector(float shift, int vectPos)
    {
        Vector3 shiftVect = new Vector3(0, 0, 0);

        switch (vectPos)
        {
            case 0:
                shiftVect.x += shift;
                break;
            case 1:
                shiftVect.y += shift;
                break;
            case 2:
                shiftVect.z += shift;
                break;
        }

        return shiftVect;
    }


    // Update is called once per frame
    void Update()
    {

    }
}
